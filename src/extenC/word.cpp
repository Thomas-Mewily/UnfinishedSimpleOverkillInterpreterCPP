#include "__base__.hpp"

void word_print(word& w, file* f)
{
    w.print(f);
}

void word::print(file* f)
{
    fprintf(f, "w64(%" usize_format "umax, %" isize_format "imax)", this->as_umax, this->as_imax);
}

#define word_impl_constructor(type) word word ## _ ## type(type val){word w; w.as_ ## type = val; return w; }
map_on_word_primitives(word_impl_constructor)