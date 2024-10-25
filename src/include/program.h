#ifndef __CHAUDER_PROGRAM
#define __CHAUDER_PROGRAM

#include <glad/gl.h>

#include "chauder.h"
#include "shader.h"

struct program_struct {
    shader_st** shaders;      // Vertex shader
    GLuint      id;           // Id of the program given by OpenGL
    int         is_compiled;  // Is the program linked
    int         nshaders;     // Number of shaders
    int         max_shaders;  // Maximum number of shaders
};

void program_realloc_shaders(program_st* prg);

#endif  // __CHAUDER_PROGRAM
