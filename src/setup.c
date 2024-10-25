#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"

#include "chauder.h"
#include "log.h"

void chauder_init(int argc, char** argv) { 
    printf("Initializing chauder.\n");
    for (int i = 0; i < argc; ++i){
        printf("\t Arg %d : %s\n", i, argv[i]);
    }

}

void chauder_finalize(void) {

}
