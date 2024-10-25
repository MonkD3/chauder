#include "chauder.h"
#include "program.h"
#include "shader.h"
#include "log.h"

#include <stdlib.h>
#include <assert.h>

program_st* program_new(void){
    program_st* ret = calloc(1L, sizeof(program_st));
    ret->shaders = malloc(sizeof(shader_st*)*8);
    ret->nshaders = 0;
    ret->max_shaders = 8;

    DEBUG("Malloc'd program_st structure at address %p", ret);
    return ret;
}

void program_destroy(program_st *prg){
    if (prg->shaders) free(prg->shaders);
    DEBUG("Free'd program_st at address %p", prg);
    free(prg);
}


// Setter
void program_add_shader(program_st* prg, shader_st* shd){
    assert(prg != NULL);
    assert(shd != NULL);

    if (prg->nshaders >= prg->max_shaders) {
        program_realloc_shaders(prg);
    }
    prg->shaders[prg->nshaders++] = shd;
}

// Getter
shader_st* program_get_shader(program_st const* prg, GLuint shd_id){
    assert(prg != NULL);
    assert(shd_id != 0);

    for (int i = 0; i < prg->nshaders; i++){
        if (prg->shaders[i]->id == shd_id) return prg->shaders[i];
    }
    return NULL;
}
int program_get_nshaders(program_st const* prg){
    assert(prg != NULL);

    return prg->nshaders;
}

GLuint program_get_id(program_st const* prg){
    assert(prg != NULL);

    return prg->id;
}

error_et program_link(program_st* prg){
    assert(prg != NULL);

    prg->id = glCreateProgram();
    if (!prg->id) {
        ERROR("A problem occured when creating the program");
        return PROGRAM_CREATE_ERROR;
    }
    return program_update(prg);
}

void program_realloc_shaders(program_st* prg){

    prg->max_shaders *= 2;
    shader_st** new = realloc(prg->shaders, sizeof(shader_st*) * prg->max_shaders);
    prg->shaders = new;
}

error_et program_update(program_st* prg){
    
    int update = !prg->is_compiled;

    for (int i = 0; i < prg->nshaders; i++){
        if (!prg->is_compiled || shader_update(prg->shaders[i])) {
            // Attach updated shaders
            DEBUG("Attaching shader '%s' at program %d", prg->shaders[i]->fname, prg->id);
            glAttachShader(prg->id, prg->shaders[i]->id);
            update = 1;
        }
    }

    if (update) {
        glLinkProgram(prg->id);

        GLint res;
        int log_len;

        // Check the program
        glGetProgramiv(prg->id, GL_LINK_STATUS, &res);
        glGetProgramiv(prg->id, GL_INFO_LOG_LENGTH, &log_len);
        if ( log_len > 0 ){
            char* err_msg = malloc(log_len+1);
            glGetProgramInfoLog(prg->id, log_len+1, NULL, err_msg);
            err_msg[log_len] = '\0';
            ERROR("%s\n", err_msg);
            free(err_msg);
            return PROGRAM_LINK_ERROR;
        }
        prg->is_compiled = 1;
    }
    return CHAUDER_SUCCESS;
}
