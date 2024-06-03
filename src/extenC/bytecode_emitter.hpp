#ifndef extenC__bytecode_emitter
#define extenC__bytecode_emitter

#include "__base__.hpp"

struct bytecode_emitter
{
    bytecode codes;

    public:
    bytecode_emitter();
    void  drop();

    usize length();


    usize push(vm_code c);
    void push_word_of_X_bytes(usize nbByte);
    void u(umax val);
    //usize push(vm_code c);

    void  print(file* f = stdout);

};



#endif