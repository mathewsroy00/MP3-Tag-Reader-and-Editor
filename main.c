/*
 * Project Name     : MP3 Tag Reader and Editor
 * Author           : Mathews Roy
 * Date             : 25-10-25
 *
 * Description      : A command-line application to read and modify ID3 tags in MP3 files.
 *                    Supports viewing all tags (Title, Artist, Album, Year, Genre, Comment) and 
 *                    editing individual tags with user-specified values.
 *                    Handles endianness conversion and maintains file integrity during modifications.
 *
 * Features         : - View ID3 tags from MP3 files
 *                    - Edit specific tags (Title, Artist, Album, Year, Genre, Comment)
 *                    - Validates ID3 format and command-line arguments
 *                    - Big-endian to little-endian conversion for cross-platform compatibility
 *
 * Usage            : View: ./a.out -v filename.mp3
 *                    Edit: ./a.out -e -t/-a/-A/-y/-C/-c new_value filename.mp3
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char* argv[])
{
    // Validate command-line arguments
    if(validate_CML_args(argc, argv) == 0)
    {
        print_errorUsage(argv);
        return 1;
    }
    
    // Display help menu
    if(argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        print_help_menu();
        return 0;
    }

    // View MP3 tags
    if(strcmp(argv[1], "-v") == 0)
    {
        mp3_view(argv);
    }
    // Edit MP3 tags
    else if(strcmp(argv[1], "-e") == 0)
    {
        mp3_edit(argv);
    }
    
    return 0;
}