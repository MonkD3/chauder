#ifndef __CHAUDER_SHADER
#define __CHAUDER_SHADER

#include "chauder.h"
#include <glad/gl.h>
#include <time.h>

struct shader_struct {
    char const* fname;  // Name
    GLuint      id;     // ID of the shader given by OpenGL
    GLenum      type;   // Shader type
    struct timespec mtime;   // File stat, to compare modification time
};
error_et shader_readcompile(shader_st* shd);

#endif  // __CHAUDER_SHADER
