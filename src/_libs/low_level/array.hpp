#ifndef low_level__array
#define low_level__array
#include "__base__.hpp"

/* 
    C array with a know length.

    Compilation mode :
    debug  : idx checked.
    release: idx not checked 
*/
template<typename T>
class array
{
    public:

    explicit array(usize size);
    explicit array();
    array(initializer_list<T> initList);

    void drop();
    void resize(usize length);
    bool try_resize(usize length);
    array<T> clone();

    T& operator[](usize index);
    const T& operator[](usize index) const;
    // compare content
    bool operator==(const array<T>& b) const;
    // compare content
    bool operator!=(const array<T>& b) const;

    void print(void (*print_fn) (T& val, file* f) = null, file* f = stdout);

    usize length() const;
    bool is_empty() const;

    bool idx_valid(usize index) const;

    protected:
    T* data    = null;
    usize len  = 0;

};

#include "array_impl.hpp"
#endif
