#ifndef _UTIL_FILE_H
#define _UTIL_FILE_H
#include <stdlib.h>
#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_END
#endif

EXTERN_C
void set_cwdir_to_bin_dir();
int relative_to_full_path(const char* relative_filepath, size_t max_bytes, const char **output);
size_t get_file_size(const char* filepath);
const char* get_base_path();
int load_file_into_buffer(const char *filepath, size_t max_bytes, const char **output);
char* file_to_string(const char* filename, size_t max_bytes, char **output);
EXTERN_C_END

#endif
