#ifndef primitives__boolean
#define primitives__boolean

#ifndef __cplusplus
#define true 1
#define false (!true)

#define bool int
#endif

#define bool_format "d"

#define primitives_map_on_boolean(macro)\
    macro(bool)

#endif