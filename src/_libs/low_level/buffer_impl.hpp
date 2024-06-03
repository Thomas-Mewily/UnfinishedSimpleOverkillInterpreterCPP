#ifndef low_level__buffer_impl
#define low_level__buffer_impl
#include "__base__.hpp"

template <typename T>
buffer<T>::buffer(usize size) 
{
    data = size == 0 ? null : make_array(T, size);
    only_in_debug(len = size);
}

template <typename T>
buffer<T>::buffer() 
{
    data = null;
    only_in_debug(len = 0);
}

template<typename T>
buffer<T>::buffer(initializer_list<T> initList)
{
    only_in_debug(len = initList.size());
    data = make_array(T, initList.size());

    usize i = 0;
    for (const T& element : initList)
    {
        data[i++] = element;
    }
}

template <typename T>
void buffer<T>::drop() {
    free(data);
    data = null;
    only_in_debug(len = 0);
}

template <typename T>
T& buffer<T>::operator[](usize index)
{
    only_in_debug(check(idx_valid(index)));
    return data[index];
}

template <typename T>
const T& buffer<T>::operator[](usize index) const
{
    only_in_debug(check(idx_valid(index)));
    return data[index];
}

only_in_debug(
    template <typename T>
    usize buffer<T>::length() const
    {
        return len;
    }
);


only_in_debug(
    template <typename T>
    bool buffer<T>::idx_valid(usize index) const
    {
        return index < len;
    }
);


template <typename T>
void buffer<T>::resize(usize length) 
{
    if(try_resize(length) == false)
    {
        crash_silent;
    }
}

template <typename T>
bool buffer<T>::try_resize(usize length) 
{
    T* data_new = (T*)realloc(data, length*sizeof(T));
    if(data_new == null){ return false;}
    data = data_new;
    only_in_debug(len = length);
    return true;
}

template <typename T>
bool buffer<T>::operator==(const buffer<T>& b) const
{
    return data == b.data;
}

template <typename T>
bool buffer<T>::operator!=(const buffer<T>& b) const { return !(*this == b); }

template <typename T>
void buffer<T>::print(void (*print_fn) (T& val, file* f), file* f)
{
    fprintf(f, "buffer at %p", data);

    only_in_debug(
        primitives_try_get_printing_function
        check(print_fn != null);

        fprintf(f, " : debug ");

        if(length() <= 0)
        {
            fprintf(f, "[]\n");
            return;
        }
        fprintf(f, "[");
        usize i = 0;
        goto middle;
        while(i < length())
        {
            fprintf(f, COLOR_FOREGROUND_WHITE ", ");
            middle:
            fprintf(f, "%s", COLOR_FOREGROUND_YELLOW);
            print_fn((*this)[i], f);
            i++;
        }
        fprintf(f, COLOR_FOREGROUND_WHITE "]");
    )
    fprintf(f, "\n");
}

#endif