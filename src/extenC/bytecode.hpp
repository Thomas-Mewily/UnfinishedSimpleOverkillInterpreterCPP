#ifndef extenC__bytecode
#define extenC__bytecode

#include "__base__.hpp"

#define uvmcode u8

#define bc_max uvmcode ## _max
#define bc_min uvmcode ## _min

struct vm_code
{
    uvmcode value;
    vm_code(uvmcode val);

    operator uvmcode() const ;

    void print(file* f = stdout);

    static void print_all(file* f = stdout);
};

#define vm_code_format glue(uvmcode,_format)
#define vm_code_format_hexa glue(uvmcode,_format_hexa)

struct bytecode
{
    vec<vm_code> vm_codes;

    usize length();

    usize push(vm_code c);

    bytecode();
    void drop();

    void print(file* f = stdout);
};



#define begin(val) case (OP(val)):
#define end break;

#define op(code) OP(code)

#define TMP_OP(code) tmp_op_ ## code
#define OP(code) op_ ## code

// Read in reverse order : C > B > A
#define READ_A(type)  (stack.pop().as_ ## type)
#define READ_B(type)  (stack.pop().as_ ## type)
//#define READ_C(type)  (stack.pop().as_ ## type)

#define OBSERVE_A(type)  (stack[stack.length()-2].as_ ## type)
#define OBSERVE_B(type)  (stack[stack.length()-1].as_ ## type)

#define SET_R_TO(val) {r = (val);};

#define DEFAULT_ERROR_ACTION
#define NO_CHECK false

#define DEFINE_OP_CODE(macro, name, impl) macro(name, impl)

#pragma region Binary Operator


#define BIN_FN_CHECK_LENGTH                   \
    only_in_debug(check(stack.length() >= 2));\


#define BIN_FN_OBSERVE_A_B(typeA, typeB)\
    BIN_FN_CHECK_LENGTH        \
    typeB b = OBSERVE_B(typeB);\
    typeA a = OBSERVE_A(typeA);\

#define BIN_FN_READ_A_B(typeA, typeB)\
    BIN_FN_CHECK_LENGTH     \
    typeB b = READ_B(typeB);\
    typeA a = READ_A(typeA);\

//Todo : I hope the C++ compiler will optimize this... (pop() x2)
#define BIN_FN_READ_IMPL(macro, instruction_name, typeA, typeB, action)                                     \
    DEFINE_OP_CODE(macro, instruction_name,                                                                 \
    {                                                                                                       \
        BIN_FN_READ_A_B(typeA, typeB)                                                                       \
        action                                                                                              \
    })

#define BIN_FN_OBSERVE_IMPL(macro, instruction_name, typeA, typeB, action)                                  \
    DEFINE_OP_CODE(macro, instruction_name,                                                                 \
    {                                                                                                       \
        BIN_FN_OBSERVE_A_B(typeA, typeB)                                                                    \
        action                                                                                              \
    })


#define BIN_OP_IMPL(macro, type, output_type, instruction, operation_block, check_exp_bool, error_action)   \
    BIN_FN_READ_IMPL(macro, type ## _ ## instruction, type, type,                                           \
    {                                                                                                       \
        output_type r;                                                                                      \
        if(!(check_exp_bool)) { error_action; }                                                             \
        operation_block;                                                                                    \
        stack.push(word_ ## output_type(r));                                                                \
    })

// Binary Operande to 1 Operande (a: left, b: right) -> r:result
#define BIN_OP_R(macro, type, output_type, instruction, expression) \
    BIN_OP_IMPL(macro, type, output_type, instruction, SET_R_TO(expression), NO_CHECK, DEFAULT_ERROR_ACTION)

#define BIN_OP_OUTPUT(macro, type, output_type, instruction, expression) \
    BIN_OP_R(macro, type, output_type, instruction, expression)

#define BIN_OP_B_NON_ZERO(macro, type, instruction, expression) \
    BIN_OP_IMPL(macro, type, type, instruction, SET_R_TO(expression), (b != 0), crash(#type "_" #instruction " by 0"))

// Binary Operande to 1 Operande (a: left, b: right)
#define BIN_OP(macro, type, instruction, expression)  BIN_OP_OUTPUT(macro, type, type, instruction, expression)

#pragma endregion

#pragma region Unary Operator

#define UNARY_FN_OUTPUT(macro, instruction_name, typeA, action) \
    DEFINE_OP_CODE(macro, instruction_name,                     \
    {                                                           \
        only_in_debug(check(stack.length() >= 1));              \
        typeA a = stack[stack.length()-1].as_ ## typeA;         \
        action                                                  \
    })

#define UNARY_OP_OUTPUT(macro, type, output_type, instruction, expression) \
    UNARY_FN_OUTPUT(macro, type ## _ ## instruction, type,                 \
    {                                                                      \
        stack[stack.length()-1] = word_ ## output_type(expression);        \
    })

#define UNARY_OP(macro, type, instruction, expression) UNARY_OP_OUTPUT(macro, type, type, instruction, expression)
#pragma endregion

#pragma region Push Const and From Byte (u8)

#define TYPE_PUSH_CONST(macro, type, val)        \
    DEFINE_OP_CODE(macro, type ## _push_ ## val,{\
        stack.push(word_wmax(val));          \
    })


#define PUSH_1B(macro, type)                            \
    DEFINE_OP_CODE(macro, type ## _push_1B, {           \
        stack.push(word_ ## type ((type)bc[bc_idx++])); \
    })

#define PUSH_2B(macro, type)                 \
    DEFINE_OP_CODE(macro, type ## _push_2B, {\
        stack.push(word_ ## type ((type)(((type)bc[bc_idx+1] << 8) | ((type)bc[bc_idx])))); \
        bc_idx += 2; \
    })

#define PUSH_4B(macro, type) \
    DEFINE_OP_CODE(macro, type ## _push_4B, { \
        stack.push(word_ ## type ((type)(((type)bc[bc_idx+3] << 24) | ((type)bc[bc_idx+2] << 16) | ((type)bc[bc_idx+1] << 8) | ((type)bc[bc_idx])))); \
        bc_idx += 4; \
    })

#define PUSH_8B(macro, type) \
    DEFINE_OP_CODE(macro, type ## _push_8B, {\
        stack.push(word_ ## type ((type)(((type)bc[bc_idx+7] << 56) |((type)bc[bc_idx+6] << 48) | ((type)bc[bc_idx+5] << 40) | ((type)bc[bc_idx+4] << 32) | ((type)bc[bc_idx+3] << 24) |((type)bc[bc_idx+2] << 16) |((type)bc[bc_idx+1] << 8) | ((type)bc[bc_idx])))); \
        bc_idx += 8; \
    })

#pragma endregion


#pragma region Arithemtic

#define SHARED_ARITHMETIC(macro, type) \
    BIN_OP(macro, type, add, a + b)  \
    BIN_OP(macro, type, sub, a - b)  \
    BIN_OP(macro, type, mul, a * b)  \
    /* no / (div) and % (mod) because it depend on the type*/ \
    /* int division by 0 => crash. float => NaN */ \
    UNARY_OP(macro, type, neg    , -a) \
    \
    BIN_OP_OUTPUT(macro, type, bool, eq,  a == b)     \
    BIN_OP_OUTPUT(macro, type, bool, neq, a != b)     \
    BIN_OP_OUTPUT(macro, type, bool, greater, a > b)  \
    BIN_OP_OUTPUT(macro, type, bool, smaller, a < b)  \
    BIN_OP_OUTPUT(macro, type, bool, greater_or_eq, a >= b)  \
    BIN_OP_OUTPUT(macro, type, bool, smaller_or_eq, a <= b)  \
    \
    TYPE_PUSH_CONST(macro, type, 0) \
    TYPE_PUSH_CONST(macro, type, 1) \
    TYPE_PUSH_CONST(macro, type, 2) \
    TYPE_PUSH_CONST(macro, type, 4) \
    TYPE_PUSH_CONST(macro, type, 8) \

#define INTEGER_SHARED_ARITHMETIC(macro, type) \
    SHARED_ARITHMETIC(macro, type)\
    \
    BIN_OP_B_NON_ZERO(macro, type, div, a / b)  \
    BIN_OP_B_NON_ZERO(macro, type, mod, a % b)  \

#define INTEGER_UNSIGNED_ARITHMETIC(macro, type) \
    INTEGER_SHARED_ARITHMETIC(macro, type)\

#define INTEGER___SIGNED_ARITHMETIC(macro, type) \
    INTEGER_SHARED_ARITHMETIC(macro, type)\

#define INTEGER_ARITHMETIC(macro, precision) \
    INTEGER_UNSIGNED_ARITHMETIC(macro, u ## precision)\
    INTEGER___SIGNED_ARITHMETIC  (macro, i ## precision)\

// Division don't crash if 0 => NaN
// Modulo operator % is not defined for float, use fX_mod instead
#define FLOATING_ARITHMETIC(macro, type) \
    SHARED_ARITHMETIC(macro, type)  \
    BIN_OP(macro, type, div, a / b) \
    BIN_OP(macro, type, mod, type ## __mod(a, b)) \

#define BIT_ARITHMETIC(macro, type) \
    BIN_OP(macro, type, and   , a & b) \
    BIN_OP(macro, type, or    , a | b) \
    BIN_OP(macro, type, xor   , a ^ b) \
    \
    BIN_OP(macro, type, rshift, a >> b)\
    BIN_OP(macro, type, lshift, a << b)\
    \
    UNARY_OP(macro, type, bitwise, ~a) \
    UNARY_OP(macro, type, not    , !a) \

#define WORD_ARITHMETIC(macro, type)\
    BIT_ARITHMETIC(macro, type)     \
    UNARY_FN_OUTPUT(macro, type ## _dup, type, { stack.push(glue(word_,type)(a)); })\
    PUSH_1B(macro, type)\
    PUSH_2B(macro, type)\
    PUSH_4B(macro, type)\
    PUSH_8B(macro, type)\

#define VM_LOOP_EXIT\
    vm_end: printf_title("end of the vm loop");

/*
if_then_goto
(bool, adr) -> void
*/ 

#define DEFINE_IF_THEN_GOTO(macro)\
    BIN_FN_READ_IMPL(macro, if_zero_goto,     umax, usize, { if(a == 0) { bc_idx = b; }}) \
    BIN_FN_READ_IMPL(macro, if_non_zero_goto, umax, usize, { if(a != 0) { bc_idx = b; }}) \


#define DEFINE_DEBUG(macro)\
    DEFINE_OP_CODE(macro, dbg, { debug; print(); })

#define MAP_ON_VM_CODE(macro)\
    DEFINE_OP_CODE(macro, stop, {goto vm_end;}) \
    DEFINE_OP_CODE(macro, nop , /*no operation : do nothings*/) \
    DEFINE_IF_THEN_GOTO(macro)\
    DEFINE_DEBUG(macro)\
    \
    WORD_ARITHMETIC(macro, wmax)\
    /*WORD_ARITHMETIC(macro,   w8) WORD_ARITHMETIC(macro,  w16) WORD_ARITHMETIC(macro,  w32) WORD_ARITHMETIC(macro,  w64)*/\
    \
    /*INTEGER_UNSIGNED_ARITHMETIC(macro, umax ) INTEGER_UNSIGNED_ARITHMETIC(macro, usize) INTEGER_UNSIGNED_ARITHMETIC(macro, uptr )*/\
    INTEGER_UNSIGNED_ARITHMETIC(macro, u8   )\
    INTEGER_UNSIGNED_ARITHMETIC(macro, u16  )\
    INTEGER_UNSIGNED_ARITHMETIC(macro, u32  )\
    INTEGER_UNSIGNED_ARITHMETIC(macro, u64  )\
    \
    /*INTEGER___SIGNED_ARITHMETIC(macro, imax ) INTEGER___SIGNED_ARITHMETIC(macro, isize) INTEGER___SIGNED_ARITHMETIC(macro, iptr )*/\
    INTEGER___SIGNED_ARITHMETIC(macro, i8   )\
    INTEGER___SIGNED_ARITHMETIC(macro, i16  )\
    INTEGER___SIGNED_ARITHMETIC(macro, i32  )\
    INTEGER___SIGNED_ARITHMETIC(macro, i64  )\
    \
    FLOATING_ARITHMETIC(macro, f32)\
    FLOATING_ARITHMETIC(macro, f64)\

#pragma endregion

#define map_on_vm_code MAP_ON_VM_CODE

#define DECLARE_OP(name, impl) OP(name),
#define DECLARE_TMP_OP(name, impl) TMP_OP(name),

//tmp_ ## DECLARE_OP(name, impl)

#define IMPL_OP(name, impl)  \
    begin(name)              \
        impl;                \
    end;                     \


#define VM_LOOP_BEGIN forever{
#define VM_LOOP_END   }


#ifdef VM_PRINT_EACH_STEP
    #define VM_DEBUG_INSTRUCTION\
    {\
        printf("executing : ");\
        ((vm_code)(VM_OBSERVE_OP)).print();\
        /*printf(" stack ");*/\
        /*stack.print(word_print);*/\
        printf("\n");\
    }\

#else
        #define VM_DEBUG_INSTRUCTION
#endif
    

#define VM_READ_OP    ((uvmcode)bc[bc_idx++])
#define VM_OBSERVE_OP ((uvmcode)bc[bc_idx])

#define VM_SWITCH\
    VM_DEBUG_INSTRUCTION\
    switch (VM_READ_OP)\
    {\
        MAP_ON_VM_CODE(IMPL_OP)\
    }\


typedef enum
{
    MAP_ON_VM_CODE(DECLARE_TMP_OP)

    tmp_op_error,
} op_code_enum;

#define op_error (op_code_enum::tmp_op_error)
#define op_code_length ((usize)op_error)

#define foreach_op_code(_varName) repeat(_varName, op_code_length)

#define op_code_declare_const_value(val, impl) const uvmcode op(val) = op_code_enum::glue(tmp_, op(val));
MAP_ON_VM_CODE(op_code_declare_const_value)


vm_code op_code_from_str(char* str);
const char* op_code_to_string(usize val);

#endif