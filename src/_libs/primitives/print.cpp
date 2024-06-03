#include "__base__.hpp"

#define primitives_implement_printf(type)\
    void type ## _ ## print(type& t, file* f) { fprintf(f, "%" glue(type,_format), t);}

primitives_map_on(primitives_implement_printf)