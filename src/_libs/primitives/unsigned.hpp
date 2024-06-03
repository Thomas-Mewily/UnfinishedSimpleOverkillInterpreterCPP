#ifndef primitives__unsigned
#define primitives__unsigned
#include "__base__.hpp"

// typedef
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

// These 3 should be the same
typedef uintptr_t nuint; // aka uint in extenC
typedef uintptr_t usize;
typedef uintptr_t uptr;

typedef uintmax_t umax;
#define usize_error (UINTPTR_MAX)

#define primitives_map_on_unsigned(macro)\
    macro(u8) macro(u16) macro(u32) macro(u64)\
    macro(nuint) macro(usize) macro(uptr)\
    macro(umax)\

// min :
#define u8_min  ((u8 )0)
#define u16_min ((u16)0)
#define u32_min ((u32)0)
#define u64_min ((u64)0)

#define nuint_min ((nuint)0)
#define usize_min ((usize)0)
#define uptr_min  ((uptr )0)
#define umax_min  ((umax )0)


// max :
#define u8_max  UINT8_MAX
#define u16_max UINT16_MAX
#define u32_max UINT32_MAX
#define u64_max UINT64_MAX

#define nuint_max UINTPTR_MAX
#define usize_max UINTPTR_MAX
#define uptr_max  UINTPTR_MAX
#define umax_max  UINTMAX_MAX

// format :
#define u8_format  PRIu8
#define u16_format PRIu16
#define u32_format PRIu32
#define u64_format PRIu64

#define nuint_format PRIuPTR
#define usize_format PRIuPTR
#define uptr_format  PRIuPTR
#define umax_format  PRIuPTR


#define u8_format_hexa  PRIx8
#define u16_format_hexa PRIx16
#define u32_format_hexa PRIx32
#define u64_format_hexa PRIx64

#define nuint_format_hexa PRIxPTR
#define usize_format_hexa PRIxPTR
#define uptr_format_hexa  PRIxPTR
#define umax_format_hexa  PRIxPTR

#endif