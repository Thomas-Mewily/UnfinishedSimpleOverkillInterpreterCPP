#ifndef primitives__base
#define primitives__base

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../__flags__.hpp"

#include "macro.hpp"

#include "boolean.hpp"
#include "signed.hpp"
#include "unsigned.hpp"
#include "floating.hpp"
#include "text.hpp"

#define primitives_map_on(macro)\
    primitives_map_on_unsigned(macro)\
    primitives_map_on_signed  (macro)\
    primitives_map_on_floating(macro)\
    primitives_map_on_boolean (macro)\
    primitives_map_on_ptr     (macro)\

#include "pointer.hpp"


#include "print.hpp"

#endif