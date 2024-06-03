#ifndef low_level__buffer
#define low_level__buffer
#include "__base__.hpp"

/* 
    C pointer with an unknow length.

    Compilation mode :
    debug  : idx checked. length is know but hidden
    release: idx not checked. length is unknow. Watch out for buffer overflow
*/
template<typename T>
class buffer
{
    public:

    explicit buffer(usize size);
    explicit buffer();
    buffer(initializer_list<T> initList);

    void drop();
    void resize(usize length);
    bool try_resize(usize length);

    T& operator[](usize index);
    const T& operator[](usize index) const;
    // compare addresse
    bool operator==(const buffer<T>& b) const;
    // compare addresse
    bool operator!=(const buffer<T>& b) const;

    protected:
    T* data    = null;

    void print(void (*print_fn) (T& val, file* f) = null, file* f = stdout);

    only_in_debug(
        usize len  = 0;
        bool idx_valid(usize index) const;
        usize length() const;
    );
};

#include "buffer_impl.hpp"
#endif
