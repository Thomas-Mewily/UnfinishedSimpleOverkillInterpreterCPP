#ifndef primitives__pointer
#define primitives__pointer

typedef void* ptr;
typedef void (*ptr_func)(void);

#define ptr_format "p"

#define primitives_map_on_ptr(macro)\
    macro(ptr)

typedef usize hash;
#define hash_format usize_format

#ifdef __cplusplus
#define null nullptr
#else
#define null ((void*)(0))
#endif

#if 0

#define it    /*Iterator. Don't own the memory*/
#define mut   /*Mutable.  Don't own the memory*/
#define ref   /*immutable.Don't own the memory*/
#endif

#define not_owned  /*Don't own the memory. Don't drop the value when your are done with the pointer*/
#define owned   /*Own the memory. Point at the beginning of the block. Drop the value when your are done with the pointer*/

#define maybe   /*Maybe the pointer is null*/

#define imut /*imutable data type*/

#define immediate /* consume the pointer right away, because it will be a andling ptr soon */

#endif