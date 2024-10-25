#ifndef __CHAUDER_INTERFACE
#define __CHAUDER_INTERFACE

#ifdef __cplusplus
extern "C" {
#endif

#include <glad/gl.h>
#include <stdbool.h>

// ====================== Errors =================================
enum error_enum {
    CHAUDER_SUCCESS = 0,
    SHADER_UPDATE,
    SHADER_NO_UPDATE,
    SHADER_READ_ERROR,
    SHADER_COMPILE_ERROR,
    PROGRAM_LINK_ERROR,
    PROGRAM_CREATE_ERROR,
};
typedef enum error_enum error_et;

// ===================== Basic functions =========================
// Setup and finalize
void chauder_init(int argc, char** argv);
void chauder_finalize(void);

// ====================== Shaders ================================
typedef struct shader_struct shader_st;  // Opaque type

// Constructor/Destructor
__attribute__((nonnull)) 
    void shader_destroy(shader_st* shd);
__attribute__((malloc, malloc(shader_destroy, 1))) 
    shader_st* shader_new(void);

// Setter
void shader_set_fname(shader_st* shd, char const* fname);
void shader_set_type(shader_st* shd, GLenum type);

// Getter
char const*  shader_get_fname(shader_st const* shd);
unsigned int shader_get_id(shader_st const* shd);

error_et shader_compile(shader_st* shd);
bool     shader_update(shader_st* shd);

// ====================== Programs ===============================
typedef struct program_struct program_st;

// Constructor/Destructor
__attribute__((nonnull)) 
    void program_destroy(program_st* prg);
__attribute__((malloc, malloc(program_destroy, 1))) 
    program_st* program_new(void);

// Setter
void program_add_shader(program_st* prg, shader_st* shd);

// Getter
shader_st* program_get_shader(program_st const* prg, GLuint const shd_id);
int        program_get_nshaders(program_st const* prg);
GLuint     program_get_id(program_st const* prg);

error_et program_link(program_st* prg);
error_et program_update(program_st* prg);

#ifdef __cplusplus
}
#endif

#endif  // __CHAUDER_INTERFACE
