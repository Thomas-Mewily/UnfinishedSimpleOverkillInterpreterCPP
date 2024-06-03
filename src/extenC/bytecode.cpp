#include "__base__.hpp"

void print_bc_line(file* f, vm_code b)
{
    b.print();
    fprintf(f, "\n");
}

vm_code::vm_code(u8 val) : value(val) {}

vm_code::operator u8() const {
    return value;
}

usize bytecode::push(vm_code c)
{
    usize len = vm_codes.length();
    vm_codes.push(c);
    return len;
}

bytecode::bytecode()
: vm_codes()
{}

usize bytecode::length() { return this->vm_codes.length(); }

void bytecode::print(file* f)
{
    fprintf_title(f, "bytecode");
    foreach_idx(i, this->vm_codes)
    {
        fprintf(f, COLOR_FOREGROUND_MAGENTA "%3" usize_format " | " COLOR_RESET, i);
        this->vm_codes[i].print(f);
        fprintf(f, "\n");
        //(*this)[i].print();
    }
    fprintf(f, "\n");
}

void bytecode::drop()
{
    this->vm_codes.drop();
}

void vm_code::print(file* f)
{
    fprintf(f, COLOR_FOREGROUND_GREEN "%3" vm_code_format  " 0x%02" vm_code_format_hexa COLOR_RESET, this->value, this->value);
    //((vm_code)o).print(f);
    fprintf(f, " > " COLOR_DEBUG_IDENTIFIER "%-24s" COLOR_RESET, op_code_to_string(this->value));
}

void vm_code::print_all(file* f)
{
    fprintf_title(f, "All the vm_codes");
    foreach_op_code(o)
    {
        print_bc_line(f, (vm_code)o);
    }
    fprintf(f, "\n");
}


vm_code op_code_from_str(char* str)
{
    #define _op_code_compare_to_string(name, impl)\
    if(strcmp(str, #name) == 0) { return op(name); }

    map_on_vm_code(_op_code_compare_to_string);
    return op_error;
}


static const char* const _op_code_names[] = 
{
    #define _op_code_val_to_string(name, impl) #name,
    map_on_vm_code(_op_code_val_to_string)
};
const char* op_code_to_string(usize val)
{
    return(val >= op_code_length) ? "error" : _op_code_names[val];
}