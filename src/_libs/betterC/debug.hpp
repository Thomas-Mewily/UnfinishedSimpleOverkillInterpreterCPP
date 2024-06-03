#ifndef betterCPP__debug
#define betterCPP__debug
#include "__base__.hpp"

#define current_file __FILE__
#define current_line __LINE__
#define current_func __func__ 
#define current_time __TIME__ 

#define print_debug  { printf("at function %s() : %s%s:%i%s\n", current_func, COLOR_DEBUG_DATA, current_file, (int)current_line, COLOR_RESET); }
#define debug        { printf("%sdebug%s ", COLOR_DEBUG_CATEGORY, COLOR_RESET); print_debug; }

#if IS_IN_DEBUG==1
#define only_in_debug(code) code
#define only_in_release(code) 
#else
#define only_in_debug(code)
#define only_in_release(code) code
#endif

#if TRACK_MEMORY==1
#define only_in_memory_tracked(code) code
#else
#define only_in_memory_tracked(code)
#endif

#define exit_program(error_code) { only_in_debug(trigger_debugger(true)); exit(error_code);}

#define crash_silent { printf("%scrash%s : \n", COLOR_DEBUG_CATEGORY, COLOR_RESET); print_debug; exit_program(EXIT_FAILURE); }
#define crash(msg)  { printf("%scrash%s : " msg "\n", COLOR_DEBUG_CATEGORY, COLOR_RESET); print_debug; exit_program(EXIT_FAILURE); }
#define crash_format(msg_format, ...)   { printf("%scrash%s : " msg_format "\n", COLOR_DEBUG_CATEGORY, COLOR_RESET, __VA_ARGS__); print_debug; exit_program(EXIT_FAILURE); }

#define check(condTrue) if(!(condTrue)) { crash(#condTrue); }
#define check_msg(condTrue, msg) if(!(condTrue)) { crash_format("%s was false\n " COLOR_DEBUG_ERROR msg COLOR_RESET, #condTrue); }
#define check_msg_format(condTrue, msg_format, ...) if(!(condTrue)) { crash_format("%s " COLOR_DEBUG_CATEGORY "was false :\n" COLOR_DEBUG_ERROR msg_format COLOR_RESET, #condTrue, __VA_ARGS__); }

#define check_msg_static(condTrue, msg) typedef char static_assertion_ ## msg[(condTrue)?1:-1]
#define check_static(condTrue) check_msg_static(condTrue,failed)


#define todo crash("todo")

#define trigger_debugger(cond) if(cond){ int a = 0; int b = 1; int c = b/a; unused(c); }

#define print_size(type) printf(COLOR_DEBUG_CATEGORY "sizeof(" COLOR_RESET # type COLOR_DEBUG_CATEGORY ")" COLOR_RESET " = " COLOR_FOREGROUND_GREEN "%" usize_format COLOR_RESET " bytes\n", sizeof(type))

#endif
