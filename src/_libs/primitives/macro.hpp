#ifndef primitives__macro
#define primitives__macro

#define stringify_instant(a) #a

#define stringify(a) stringify_instant(a)

#define glue_instant(a,b) a ## b
#define glue(a,b) glue_instant(a, b)

#define twice(x) x x

#define unused(x) (void)(x)

#define pri  private:
#define pub  public:

#endif