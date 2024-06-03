#ifndef extenC__cpu
#define extenC__cpu

#include "__base__.hpp"

struct cpu
{
    usize idx;
    bytecode* prog;
    fixed_vec<word> stack;

    cpu(bytecode* prog = null, usize stack_size = 512);

    void execute();
    
    void drop();
    void print(file* f = stdout);
};

#endif