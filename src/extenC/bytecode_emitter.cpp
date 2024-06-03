#include "__base__.hpp"

bytecode_emitter::bytecode_emitter()
: codes()
{}

void bytecode_emitter::print(file* f)
{
    codes.print(f);

}

void bytecode_emitter::push_word_of_X_bytes(usize nbByte)
{
    switch (nbByte)
    {
        case 0: return;
        case 1: codes.push(op_wmax_push_1B); return;
        case 2: codes.push(op_wmax_push_2B); return;
        case 4: codes.push(op_wmax_push_4B); return;
        case 8: codes.push(op_wmax_push_8B); return;
        default: crash_format("Can't push a word of %" usize_format " u8", nbByte);
    }
}


usize bytecode_emitter::length() { return this->codes.length(); }

usize bytecode_emitter::push(vm_code c)
{
    usize len = codes.length();
    codes.push(c);
    return len;
}

void bytecode_emitter::u(umax val)
{
    switch (val)
    {
        case 0: codes.push(op_u64_push_0); return;
        case 1: codes.push(op_u64_push_1); return;
        case 2: codes.push(op_u64_push_2); return;
        case 4: codes.push(op_u64_push_4); return;
        case 8: codes.push(op_u64_push_8); return;
        default:
        {
            check_static(sizeof(umax) == sizeof(u64));

            usize nbByte = 0;
            if(val < power_of_2( 8)) { nbByte = 1; } else
            if(val < power_of_2(16)) { nbByte = 2; } else
            if(val < power_of_2(32)) { nbByte = 4; } else
                                     { nbByte = 8; } 

            check(nbByte != 0);
            push_word_of_X_bytes(nbByte);

            while(nbByte != 0)
            {
                u8 m = (u8)(val & 0xFF);
                val = val >> 8;
                codes.push(m);
                nbByte--;
            }
        }
        break;
    }
}

void bytecode_emitter::drop()
{
    codes.drop();
}
