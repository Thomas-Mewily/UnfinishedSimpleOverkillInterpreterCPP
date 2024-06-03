#ifndef primitives__print
#define primitives__print
#include "__base__.hpp"

#define primitives_declare_printf(type)\
    void type ## _ ## print(type& t, file* f = stdout);

primitives_map_on(primitives_declare_printf);

#include <type_traits>

#define primitives_impl_try_get_printing_function_fn_T(primitive_type)\
    if constexpr (std::is_same_v<T, primitive_type>)\
    {\
        print_fn = primitive_type ## _print;\
    }\

// depend on <T>. varResult name : print_fn (should be declared)
#define primitives_try_get_printing_function primitives_map_on(primitives_impl_try_get_printing_function_fn_T)

#endif