#include <utilities/file.h>
#include <utilities/logging.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void set_cwdir_to_bin_dir(){
  chdir(get_base_path());
}
const char* get_base_path(){
  #ifdef _WIN32
  static char *path = NULL;
  if(NULL == path){
    DWORD path_size = 1024;
    path = malloc(path_size);
    for (;;){//http://stackoverflow.com/a/9112949/6019199
      memset(path, 0, path_size);
      DWORD result = GetModuleFileName(0, path, path_size - 1);
      DWORD last_error = GetLastError();
      if (0 == result){
        free(path);
        path = 0;
        break;
      } else if (result == path_size - 1){
        free(path);
        /* May need to also check for ERROR_SUCCESS here if XP/2K */
        if (ERROR_INSUFFICIENT_BUFFER != last_error){
          path = 0;
          break;
        }
        path_size = path_size * 2;
        path = malloc(path_size);
      }
      else{
        break;
      }
    }
    char *end_slash = strrchr(path, '/');
    char *end_backslash = strrchr(path, '\\');
    char *end_slashes = end_slash >= end_backslash? end_slash : end_backslash;
    end_slashes[0] = '\0';
  }
  return path;
  #else
  static char *buffer = NULL;
  if(NULL == buffer){
    buffer = dirname(realpath("/proc/self/exe", NULL)); //leaky, realpath mallocs and dirname never frees, but this should only happen once for the lifetime of the program and live as long as that.
  }
  return buffer;
  #endif
}

char* file_to_string(const char* filename, size_t max_bytes, char **const output){
  FILE *pFile = fopen (filename, "rb");
  if (!pFile){
    report(FAIL, "Couldn't open %s: %s!", filename,strerror(errno));
    return NULL;
  }
  size_t size = get_file_size(filename)+1;
  if(size > max_bytes){
    if(*output != NULL){
      report(FAIL, "Buffer for %s not big enough.", filename);
      return NULL;
    }
  }
  int dynamic_buffer = !(*output);
  if(*output == NULL){
    *output = malloc(size);
    if(NULL == *output){
      report(FAIL, "Allocation of %u bytes failed : %s", size, strerror(errno));
      return NULL;
    }
  }
  const size_t elements_read = fread(*output, 1, size-1, pFile);
  if(elements_read != size-1){
    report(FAIL, "Read %lu instead of %lu bytes, errno: %s", elements_read, size, strerror(errno));
    if(dynamic_buffer)
    free(*output);
    return NULL;
  }
  (*output)[size-1] = '\0';
  return *output;
}

int relative_to_full_path(const char* relative_filepath, size_t max_bytes, char **const output){
  const char* basepath = get_base_path();
  size_t basepath_size = strlen(basepath);
  size_t relative_filepath_size = strlen(relative_filepath);
  size_t required_size = basepath_size+relative_filepath_size+2; // +1 for null char
  if(required_size > max_bytes){
    if(NULL != *output){
      report(FAIL, "Buffer not big enough & no null ptr provided");
      return -1;
    }
    *output = malloc(required_size);
    if(NULL == *output){
      report(FAIL, "Buffer allocation failed!");
      return -1;
    }
  }
  strcpy(*output, basepath);
  strcat(strcat(*output, "/"), relative_filepath);
  return 0;
}

size_t get_file_size(const char* filepath){
  struct stat st;
  stat(filepath, &st);
  return st.st_size;
}
