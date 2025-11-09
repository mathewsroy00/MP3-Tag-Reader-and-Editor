/*
 * Name             : Mathews Roy
 * Date             : 25-10-25
 * Function Name    : mp3_view
 *
 * Description      : Reads and displays metadata (ID3v2 tags) from an MP3 file.
 *                    Validates whether the file contains an ID3 header.
 *                    Reads and prints information such as Title, 
 *                    Artist, Album, Year, Genre, and Comment.
 *                    Matches each tag's frame ID (like TIT2, TPE1, etc.) with 
 *                    its corresponding label using a array of labels and tags.
 *                    Converts each frame size from big-endian to little-endian 
 *                    format before reading the content.
 *
 * Parameters       : char *argv[] - Command-line arguments; argv[2] should 
 *                                   contain the MP3 filename.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void mp3_view(char* argv[])
{
    // File opening
    FILE* fp = fopen(argv[2], "r");
    if(fp == NULL)
    {
        printf("File is not available\n");
        return;
    }

    // Read and validate ID3 tag
    char id[4]; 
    fread(id, 3, 1, fp); 
    id[3] = '\0';
    validate_version(id); // Function call
    
    //skipping the next 7 bytes version and flag
    fseek(fp, 7, SEEK_CUR);

    printf("................................................................................\n");
    printf("MP3 Reader and Tag Editor for ID3v2\n");
    printf("................................................................................\n");

    // for reading 6 tags
    for(int i = 0; i < 6; i++)
    { 
        // Read and storing 4 bytes tag
        char tag[5];
        fread(tag, 4, 1, fp);
        tag[4] = '\0';

        // For printing the names according to the  tag
        char tags[6][5] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
        char names[6][10] = {"Title", "Artist", "Album", "Year", "Music", "Comment"};

        // comparing tag read from the file and tag in the array
        for(int j = 0; j < 6; j++)
        {
            if(strcmp(tag, tags[j]) == 0)  
            {
                printf("%-20s  :    ", names[j]);
                break;
            }
        }

        // Reading size and storing for content reading
        int size;
        fread(&size, sizeof(int), 1, fp);
    
        //converting raw size in big endian to little endian
        endian_swap(&size);
        
        // skipping 3 bytes flag-2 bytes and null-1 byte
        fseek(fp, 3, SEEK_CUR);

        // Reads content and displays
        char content[size];
        fread(content, size - 1, 1, fp);
        content[size-1] = '\0';
        printf("%-5s\n", content);
    }
    printf("................................................................................\n");
    fclose(fp);
}

void validate_version(char* id) 
{
    if(strcmp(id, "ID3") != 0)
    {
        printf("The file is not an MP3 file\n");
        exit(1);
    }
    else
    {
        printf("The file is an MP3 file\n");
    }
}

void endian_swap(int* size)
{
    char* ptr = (char*) size; // typecasting to char for swapping

    // Swapping logic
    for(int i = 0; i <= 1; i++)
    {
        char temp = ptr[i];
        ptr[i] = ptr[3 - i];
        ptr[3 - i] = temp;
    } 
}

int validate_CML_args(int argc, char* argv[])
{
    if(argc == 1 || argc == 4 || argc > 5) // checking argument count
    {
        printf("Error: Invalid number of input arguments\n");
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "--help") != 0)
    {
        printf("Error: Invalid input argument\n");
        return 0;
    }
    if(argc == 3 && strcmp(argv[1], "-v") != 0)
    {
        printf("Error: second argument should be -v / -e\n");
        return 0;
    }
    if(argc == 5 && strcmp(argv[1], "-e") != 0)
    {
        printf("Error: second argument should be -v / -e\n");
        return 0;
    }
    // For edit validation
    if(argc == 5)
    {
        // checking if tag option is valid 
        char tag_options[6][3] = {"-t", "-a", "-A", "-y", "-C", "-c"};
        int flag = 0;
        for(int i = 0; i < 6; i++)
        {
            if(strcmp(argv[2], tag_options[i]) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            printf("Error: Invalid input arguments for editing tag options\n");
            return 0;
        }
    }
    return 1;  
} 

void print_errorUsage(char* argv[])
{
    printf("------------------------------------------------------------------------\n");
    printf("ERROR: ");
    for(int i = 0; argv[i] != NULL; i++) // for printing the command line input
    {
        printf("%s ", argv[i]);
    } 
    printf(":INVALID ARGUMENTS\n");
    printf("USAGE :\n");
    printf("To view please pass like  : ./a.out -v mp3filename\n");
    printf("To edit please pass like  : ./a.out -e -t/ -a/ -A/ -y/ -C/ -c content mp3filename\n");
    printf("For help please pass like : ./a.out --help");
    printf("\n------------------------------------------------------------------------\n");
}

void print_help_menu()
{
    printf("---------------------------------------------\n");
    printf("                 HELP MENU                   \n");
    printf("---------------------------------------------\n");
    printf("1.  -v    : Displays MP3 file information\n");
    printf("2.  -e    : To modify MP3 file information\n");
    printf("     2.1  -t : Modify Title tag\n");
    printf("     2.2  -a : Modify Artist tag\n");
    printf("     2.3  -A : Modify Album tag\n");
    printf("     2.4  -y : Modify Year tag\n");
    printf("     2.5  -C : Modify Content tag\n");
    printf("     2.6  -c : Modify Comment tag\n");
    printf("---------------------------------------------\n");


}
