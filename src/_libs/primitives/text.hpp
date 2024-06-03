#ifndef primitives__text
#define primitives__text
#include "__base__.hpp"

// text & IO :
typedef u32 rune; // aka char in extenC
//#define c_string char*

#define char_eof     ((char)'\0')
#define rune_eof     ((rune)(char_eof))

#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

typedef FILE file;

#endif