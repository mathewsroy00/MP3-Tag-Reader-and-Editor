#ifndef HEADER_H
#define HEADER_H

void mp3_view(char* argv[]);
void mp3_edit(char* argv[]);

void validate_version(char* id);
void endian_swap(int* size);
int validate_CML_args(int argc, char* argv[]);
void print_errorUsage(char* argv[]);
void print_help_menu();

#endif