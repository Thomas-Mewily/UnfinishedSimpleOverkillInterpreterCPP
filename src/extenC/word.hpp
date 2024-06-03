#ifndef extenC__word
#define extenC__word

#include "__base__.hpp"


typedef umax wmax;
#define wmax_format      umax_format
#define wmax_format_hexa umax_format_hexa
#define wmax_print       umax_print

typedef u8 w8;
#define w8_format       u8_format
#define w8_format_hexa  u8_format_hexa
#define w8_print        u8_print

typedef u16 w16;
#define w16_format       u16_format
#define w16_format_hexa  u16_format_hexa
#define w16_print        u16_print

typedef u32 w32;
#define w32_format       u32_format
#define w32_format_hexa  u32_format_hexa
#define w32_print        u32_print

typedef u64 w64;
#define w64_format       u64_format
#define w64_format_hexa  u64_format_hexa
#define w64_print        u64_print

typedef uptr wptr;
#define wptr_format       uptr_format
#define wptr_format_hexa  uptr_format_hexa
#define wptr_print        uptr_print

#define map_on_word(macro)\
    macro(w8) macro(w16) macro(w32) macro(w64) \
    macro(wmax) macro(wptr)\

#define map_on_word_primitives(macro)\
    primitives_map_on(macro)\
    map_on_word(macro)
   
union word
{
    #define word_declare_field(type) type as_ ## type;
    map_on_word_primitives(word_declare_field)

    void print(file* f = stdout);
};

void word_print(word& w, file* f = stdout);

#define word_declare_constructor(type) word word ## _ ## type(type val);
map_on_word_primitives(word_declare_constructor)

#endif