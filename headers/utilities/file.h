#ifndef _UTIL_FILE_H
#define _UTIL_FILE_H

#ifdef __cplusplus
extern "C"{
#endif
#include <stdlib.h>

void set_cwdir_to_bin_dir();
int relative_to_full_path(const char* relative_filepath, size_t max_bytes, char **const output);
size_t get_file_size(const char* filepath);
const char* get_base_path();
char* file_to_string(const char* filename, size_t max_bytes, char **const output);


#ifdef __cplusplus
}
#endif
#endif
