#ifndef primitives__floating
#define primitives__floating
#include "__base__.hpp"
#include <math.h>

typedef float  float32;
typedef double float64;

typedef float  f32;
typedef double f64;
//typedef double fmax;

#define f32__mod fmodf
#define f64__mod fmodl

#define f32_format "f"
#define f64_format "lf"

#define primitives_map_on_floating(macro)\
    macro(f32) macro(f64)

#endif