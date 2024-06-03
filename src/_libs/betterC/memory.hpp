#ifndef betterCPP__memory
#define betterCPP__memory
#include "__base__.hpp"

//#define calloc(nbBytes) ((calloc)(1,nbBytes))

#define make(type) (type*)malloc(sizeof(type))
#define make_array(type, nb) (type*)memory_make_array(sizeof(type), nb)
#define realloc_array(ptr, type, nb) (type*)memory_realloc_array(ptr, sizeof(type), nb)

#ifdef TRACK_MEMORY
#define malloc(nbBytes) memory_malloc(nbBytes)
#define calloc(count, size) memory_calloc(count, size)
#define realloc(ptr, nbBytes) memory_realloc(ptr, nbBytes)
#define free(ptr) memory_free(ptr)

void* memory_malloc(usize nb_byte);
void* memory_calloc(usize count_, usize size);
void* memory_realloc(void* ptr, usize nb_byte);
void  memory_free(void* ptr);
#endif

void* memory_make_array(usize sizeof_type, usize nb_value);
void* memory_realloc_array(void* ptr, usize sizeof_type, usize nb_value);


void memory_printf_rel(usize less);
void memory_printf();
void memory_printf_final();
usize  memory_get_nb_alloc();


#define memory_copy(adr_dest, adr_source, _nb_bytes) (memcpy(adr_dest, adr_source, _nb_bytes))
#define memory_set(adr_dest, _nb_bytes, value)  (memset(adr_dest, _nb_bytes, value))
#define memory_set_0(adr_dest, _nb_bytes) (memset(adr_dest, _nb_bytes, 0))

#ifdef __cplusplus
void* operator new(usize nb_bytes);
void operator delete(void* ptr) noexcept;
#endif

#endif