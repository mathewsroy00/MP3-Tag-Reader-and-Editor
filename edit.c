/*
 * Name             : Mathews Roy
 * Date             : 25-10-25
 * Function Name    : mp3_edit
 *
 * Description      : Edits a specific ID3v2 tag in an MP3 file.
 *                    Creates a temporary file, copies the entire contents 
 *                    while replacing the content of the specified tag.
 *                    Compares each tag with the specified tag - if matched, 
 *                    content and size will be modified and remaining bytes are copied as-is.
 *                    If not matched, loop moves to the next tag.
 *                    Finally removes the old file and renames the modified file with the original name.
 *               
 * Parameters       : argv[] - Command-line arguments containing tag option, 
 *                             new value, and filename
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void mp3_edit(char* argv[])
{
    // opens original MP3 file for reading 
    FILE* fp_read = fopen(argv[4], "r");
    if(fp_read == NULL)
    {
        printf("%s file is not available\n", argv[4]);
        print_errorUsage(argv);
        return;
    }

    // opening temporary file for writing modified content
    FILE* fp_write = fopen("temp.mp3", "w");
    if(fp_write == NULL)
    {
        printf("%s file is not available\n", argv[4]);
        print_errorUsage(argv);
        return;
    }

    // Read and validate ID3 tag
    char id[4]; 
    fread(id, 3, 1, fp_read); 
    id[3] = '\0'; 
    validate_version(id); // Function call
    fwrite(id, 3, 1, fp_write);

    // For finding which tag to be modified
    int edit_index = -1;
    char tags[6][5] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
    char tag_options[6][3] = {"-t", "-a", "-A", "-y", "-C", "-c"};
    char tag_edit[5];
    for(int i = 0; i < 6; i++)
    {
        if(strcmp(argv[2], tag_options[i]) == 0)
        {
            strcpy(tag_edit, tags[i]);
            edit_index = i;
            break;
        }
    }

    // Copying first 10 bytes of header 
    char header[8];
    fread(header, 7, 1, fp_read);
    header[7] = '\0';
    fwrite(header, 7, 1, fp_write); // writing header to temporary file

    for(int i = 0; i < 6; i++)
    {
        // Reading 4 bytes of tag
        char tag1[5];
        fread(tag1, 4, 1, fp_read);
        tag1[4] = '\0';

        // checking if it is matches the modifying tag
        if(strcmp(tag1, tag_edit) == 0)
        {
            // writing tag to temp file
            fwrite(tag_edit, 4, 1, fp_write);

            // Reading original content size stored in big endian
            int old_size;
            fread(&old_size, 4, 1, fp_read);
            endian_swap(&old_size); // changing to little endian

            // calculating new content size
            int length = strlen(argv[3]);
            int new_size = length + 1; // +1 for null treminator
            
            // Converting new size to Big endian for writing into temp file
            endian_swap(&new_size); 
            fwrite(&new_size, 4, 1, fp_write);

            // Copies 3 byte flag(2 bytes) and null(1 bytes) and write to temp file
            char flag_enc[4];
            fread(flag_enc, 3, 1, fp_read);
            flag_enc[3] = '\0';
            fwrite(flag_enc, 3, 1, fp_write);

            // Converting newsize to little endian for writing content
            endian_swap(&new_size);
            fwrite(argv[3], new_size - 1, 1, fp_write);

            // Skipping old content in original file 
            fseek(fp_read, old_size - 1,  SEEK_CUR);

            // Copying all remaining bytes one by one till EOF
            int ch;
            while((ch = fgetc(fp_read)) != EOF)
            {
                fputc(ch, fp_write);
            }

            fclose(fp_read);
            fclose(fp_write);

            // Removing old file and renaming modified file to original name
            remove(argv[4]);
            rename("temp.mp3", argv[4]);

            char tag_names[6][15] = {"Title", "Artist", "Album", "Year", "Music", "Comment"};
            printf("---------------------------Selected Edit option--------------------------\n");
            printf("Tag to be edited: %s\n", tag_edit);
            printf("%s : %s\n", tag_names[edit_index], argv[3]);
            printf("---------------------------%s changed succesfully ----------------------\n", tag_names[edit_index]);
            exit(0);
        }
        else
        {
            // if tag doesn't match
            fwrite(tag1, 4, 1, fp_write);

            // copying size
            int size;
            fread(&size, 4, 1, fp_read);
            fwrite(&size, 4, 1, fp_write);

            // copying flags and null 
            char flag_version[4];
            fread(flag_version, 3, 1, fp_read);
            flag_version[3] = '\0';
            fwrite(flag_version, 3, 1, fp_write);

            // converting size to little endian
            endian_swap(&size);
            
            // copying contents
            char content[size];
            fread(content, size - 1, 1, fp_read);
            fwrite(content, size - 1, 1, fp_write);
        }
    }
}
