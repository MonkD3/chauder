#include "chauder.h"
#include <stdlib.h>

int main(int argc, char** argv){
    // Init chauder and give it the cmd line arguments
    chauder_init(argc, argv);


    // Do your stuff
    // ...


    // Finalize chauder
    chauder_finalize();
    return EXIT_SUCCESS;
}
