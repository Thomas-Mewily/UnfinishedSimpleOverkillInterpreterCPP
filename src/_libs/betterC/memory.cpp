#include "__base__.hpp"

#ifdef TRACK_MEMORY
usize memory_nb_malloc_actif = 0;

void* memory_malloc(usize nb_byte)
{
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (malloc)(nb_byte);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void* memory_calloc(usize count, usize size)
{
    usize nb_byte = count*size;
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (calloc)(count, size);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void memory_free(void* ptr)
{
    if(ptr == null) return;
    memory_nb_malloc_actif--;
    (free)(ptr);
}

void* memory_realloc(void* ptr, usize nb_byte)
{
    if(ptr == null) { return malloc(nb_byte); }
    if(nb_byte == 0) { free(ptr); }
    return (realloc)(ptr, nb_byte);
}
#endif

void* memory_make_array(usize sizeof_type, usize nb_value)
{
    check(sizeof_type*nb_value >= nb_value);
    return malloc(sizeof_type*nb_value);
}

void* memory_realloc_array(void* ptr, usize sizeof_type, usize nb_value)
{
    check_msg_format(sizeof_type*nb_value >= nb_value, "the amount of memory needed can't be stored in a single computer : usize overflow when requesting the reallocation of an array of size %" usize_format " * %" usize_format " * %" usize_format " = %% (overflow) for ptr %p" usize_format, sizeof_type, nb_value, sizeof_type*nb_value, ptr);
    return realloc(ptr, sizeof_type*nb_value);
}

void _memory_printf(usize less, bool is_final)
{
    #ifdef TRACK_MEMORY
    if(is_final){less = 0;}
    printf("%smemory %s: %s%s%i malloc actif%s\n", COLOR_FOREGROUND_GREEN, COLOR_FOREGROUND_WHITE, (!is_final || memory_nb_malloc_actif == 0) ? COLOR_FOREGROUND_WHITE : COLOR_FOREGROUND_RED, less == 0 ? "": (COLOR_FOREGROUND_YELLOW "~ " COLOR_FOREGROUND_WHITE), (int)(memory_nb_malloc_actif-less), COLOR_RESET);
    #else
    unused(less);
    unused(is_final);
    printf("%smemory %s: not tracked\n", COLOR_FOREGROUND_GREEN, COLOR_FOREGROUND_WHITE);
    #endif
}

void memory_printf_rel(usize less) { _memory_printf(less, false); }
void memory_printf_final() { _memory_printf(0, true); }
void memory_printf() { memory_printf_rel(0); }

usize memory_get_nb_alloc()
{
    #ifdef TRACK_MEMORY
    return memory_nb_malloc_actif;
    #else
    return -1;
    #endif
}

#ifdef __cplusplus
void* operator new(usize nb_bytes)
{
    return malloc(nb_bytes);
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
}

void operator delete(void* ptr, usize size) noexcept
{
    unused(size);
    free(ptr);
}
#endif