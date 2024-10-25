#ifndef __CHAUDER_IO
#define __CHAUDER_IO

#include "chauder.h"
#include <stdlib.h>

__attribute__((nonnull)) 
    error_et read_file(char const* fname, char** buf, size_t* len);

#endif // __CHAUDER_IO
