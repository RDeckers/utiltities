#include <stdlib.h>
#include <string.h>

#define DEFINE_DYNARR(SUFFIX, TYPE)\
  typedef struct dynarr##SUFFIX{TYPE *base; size_t count; size_t size;}dynarr##SUFFIX##_t;\
  int dynarr##SUFFIX##_init(dynarr##SUFFIX##_t* dynarr, unsigned Size);\
  void dynarr##SUFFIX##_deinit(dynarr##SUFFIX##_t* dynarr);\
  dynarr##SUFFIX##_t* dynarr##SUFFIX##_new(unsigned Size);\
  void dynarr##SUFFIX##_free(dynarr##SUFFIX##_t *dynarr);\
  inline void dynarr##SUFFIX##_force_push(dynarr##SUFFIX##_t *dynarr, TYPE x){\
    *((dynarr->base)+(dynarr->count++)) = x;\
  }\
\
  inline void dynarr##SUFFIX##_force_push_array(dynarr##SUFFIX##_t *dynarr, TYPE *array, size_t n){\
    memmove(dynarr->base+(dynarr->count), array, sizeof(TYPE)*n);\
    dynarr->count += n;\
  }\
  \
  int dynarr##SUFFIX##_push(dynarr##SUFFIX##_t *dynarr, TYPE x);\
  int dynarr##SUFFIX##_push_array(dynarr##SUFFIX##_t *dynarr, TYPE *array, size_t n);\
  inline TYPE dynarr##SUFFIX##_force_pop(dynarr##SUFFIX##_t *dynarr){\
    return *(dynarr->base+(--(dynarr->count)));\
  }\
\
  int dynarr##SUFFIX##_pop(dynarr##SUFFIX##_t *dynarr, TYPE *y);\
  int dynarr##SUFFIX##_shrink_to_fit(dynarr##SUFFIX##_t *dynarr);\
  int dynarr##SUFFIX##_resize(dynarr##SUFFIX##_t *dynarr, unsigned size);

#define IMPLEMENT_DYNARR(SUFFIX, TYPE)\
 int dynarr##SUFFIX##_init(dynarr##SUFFIX##_t* dynarr, unsigned Size){\
  Size  = 0 == Size? 128 : Size;\
  dynarr->base = malloc(sizeof(TYPE)*Size);\
  if(!dynarr->base){\
    return 0;\
  }\
  dynarr->count = 0;\
  dynarr->size = Size;\
  return 1;\
 }\
\
 void dynarr##SUFFIX##_deinit(dynarr##SUFFIX##_t* dynarr){\
   free(dynarr->base);\
 }\
\
  dynarr##SUFFIX##_t* dynarr##SUFFIX##_new(unsigned Size){\
    Size  = 0 == Size? 128 : Size;\
    dynarr##SUFFIX##_t* ret = malloc(sizeof(dynarr##SUFFIX##_t));\
    if(!ret) return NULL;\
    if(!dynarr##SUFFIX##_init(ret, Size)){\
      free(ret);\
      return NULL;\
    }\
	  return ret;\
  }\
\
  void dynarr##SUFFIX##_free(dynarr##SUFFIX##_t *dynarr){\
    dynarr##SUFFIX##_deinit(dynarr);\
    free(dynarr);\
  }\
\
  int dynarr##SUFFIX##_push(dynarr##SUFFIX##_t *dynarr, TYPE x){\
    if(dynarr->count >= dynarr->size){\
      dynarr->base = realloc(dynarr->base, sizeof(TYPE)*dynarr->size*2);\
      if(NULL == dynarr->base){return - 1;}\
      else{dynarr->size *= 2;}\
    }\
    dynarr##SUFFIX##_force_push(dynarr, x);\
    return 0;\
  }\
  int dynarr##SUFFIX##_push_array(dynarr##SUFFIX##_t *dynarr, TYPE *array, size_t n){\
    if(dynarr->count + n >= dynarr->size){\
      dynarr->base = realloc(dynarr->base, sizeof(TYPE)*(dynarr->size+n));\
      if(NULL == dynarr->base){return - 1;}\
      else{dynarr->size = dynarr->size+n;}\
    }\
    dynarr##SUFFIX##_force_push_array(dynarr, array, n);\
    return 0;\
  }\
\
  int dynarr##SUFFIX##_pop(dynarr##SUFFIX##_t *dynarr, TYPE *y){\
    if(dynarr->count == 0) /*will cause issues if you pop an empty dynarr.*/\
      return -1;\
    *y = dynarr##SUFFIX##_force_pop(dynarr);\
    return 0;\
  }\
  int dynarr##SUFFIX##_shrink_to_fit(dynarr##SUFFIX##_t *dynarr){\
    if(dynarr->count != dynarr->size){\
      dynarr->base = realloc(dynarr->base, sizeof(TYPE)*dynarr->count);\
      if(dynarr->base == NULL){return - 1;}\
      else{dynarr->size = dynarr->count;}\
    }\
    return 0;\
  }\
  \
  int dynarr##SUFFIX##_resize(dynarr##SUFFIX##_t *dynarr, unsigned size){\
    unsigned capacity = dynarr->size;\
    if(size > capacity){\
      dynarr->base = realloc(dynarr->base, sizeof(TYPE)*size);\
      if(!dynarr->base){\
        return -1;\
      }\
      dynarr->size = size;\
    }\
    return 0;\
  }
