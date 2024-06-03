#ifndef betterCPP__verification
#define betterCPP__verification

#include "__base__.hpp"

// Don't mess with my primitives
check_static(sizeof(usize) == sizeof(usize));
check_static(sizeof(usize) == sizeof(nuint));

check_static(sizeof(isize) == sizeof(isize));
check_static(sizeof(isize) == sizeof(nint ));

check_static(sizeof(void*) == sizeof(usize ));
check_static(sizeof(void*) == sizeof(isize ));

check_static(sizeof(char) == 1);

check_static(sizeof(u8)  == 1);
check_static(sizeof(u16) == 2);
check_static(sizeof(u32) == 4);
check_static(sizeof(u64) == 8);

check_static(sizeof(i8)  == 1);
check_static(sizeof(i16) == 2);
check_static(sizeof(i32) == 4);
check_static(sizeof(i64) == 8);

#endif