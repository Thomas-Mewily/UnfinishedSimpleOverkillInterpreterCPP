#include "__base__.hpp"

cpu::cpu(bytecode* prog, usize stack_size) : prog(prog)
{
    idx = 0;
    stack = fixed_vec<word>(stack_size);
}

void cpu::drop()
{
    idx = 0;
    prog = null;
    stack.drop();
}

void cpu::print(file* f)
{
    fprintf_title(f, "cpu");
    stack.print(word_print);
    fprintf(f, "\n");
}

// Interpreter by Mewily ^^
void cpu::execute()
{
    check(prog != null);

    vec<vm_code>& bc = prog->vm_codes;
    check(bc.idx_valid(this->idx));
    register usize bc_idx = this->idx;
    
    VM_LOOP_BEGIN
    VM_SWITCH
    VM_LOOP_END

    VM_LOOP_EXIT
    
    this->idx = bc_idx;
    return;
}


/*
stack :

coming_from
ptr_result

variables of the functions

temporary/register

*/

/*
define macro

vm_code_name_declaration vm_code_implementation 
*/