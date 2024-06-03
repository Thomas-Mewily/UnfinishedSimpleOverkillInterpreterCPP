#include "__base__.hpp"

void cpu_test_unsigned()
{
    printf_test_begin("pushing unsigned");
    vec<umax> values = vec<umax>();

    
    repeat(i, 500)
    {
        umax val = rand() *rand()*rand()*rand()+rand()*rand() +rand()+rand();
        values.push(val);
    }

    values.push(1);
    values.push(42);
    values.push(255);
    values.push(256);
    values.push(257);
    values.push(65535);
    values.push(65536);
    values.push(umax_min);
    values.push(umax_max);

    bytecode_emitter b;

    foreach_idx(i, values)
    {
        b.u(values[i]);
    }

    b.push(op_stop);
    b.print();

    cpu c = cpu(&b.codes);
    c.execute();

    
    check(c.stack.length() == values.length());
    foreach_idx(i, values)
    {
        umax wanted = values[i];
        umax got    = c.stack[i].as_umax;
        check(wanted == got);
    }
    //c.print();

    values.drop();
    b.drop();
    c.drop();

    printf_test_end();
}

void test_bc()
{
    vm_code::print_all();

    bytecode code;


    /*
    op :
    conversion,
    i8  to i16
    i16 to i32
    i32 to i64

    ...
    i32 to f32
    deref ptr of type


    class : bytecode_emitter

    b.add(1,2)
    b.add(1,sub(10,30))
    b.variable("name", type)
    b.variableA
    */

   //loop from 4 to 0
   
   
    code.push(op_i32_push_4);
    code.push(op_nop);
    code.push(op_nop);
    code.push(op_wmax_dup);
    code.push(op_i32_push_1);
    code.push(op_i32_sub);
    code.push(op_wmax_dup);
    code.push(op_i32_push_2);
    code.push(op_if_non_zero_goto);


    /*
    code.push(op_i64_push_8);
    code.push(op_i64_push_0);
    code.push(op_i64_mod);
    */

    // << formatter arguments
    //code.push(op_dbg);
    
    /*
    bytecode_emitter b;

    b.push(op_i32_push_4);*/
    code.push(op_stop);
    code.print();

    //cpu c = cpu(&b.codes);
    cpu c = cpu(&code);
    c.execute();
    c.print();

    //b.drop();
    c.drop();
    code.drop();
}

// Todo
int main(int argc, char const* argv[])
{
    unused(argc);
    unused(argv);
    printf("%sCompiled%s at %s \n", COLOR_DEBUG_CATEGORY, COLOR_RESET, current_time);
    only_in_debug(low_level_verification());

    test_bc();
    //cpu_test_unsigned();
    
    //array<u32> test = {1,2,3,4,32,64,48};
    //test.print();
    //test.drop();
    
    /*
    int * p = new int;
    *p = 3;
    std::cout << *p << std::endl;
    */
   
    /*
    int n = INT_MAX-234;
    int size = sizeof(int)*n;
    int* t = (int*)(malloc)(size);
    int* tab = make_array(int, n);
    */

    repeat(i, 10)
    {
        // that my loop
    }

    memory_printf_final();
    return EXIT_SUCCESS;
}
