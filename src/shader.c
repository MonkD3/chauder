#include "chauder.h"
#include "shader.h"
#include "io.h"
#include "log.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

shader_st* shader_new(void){
    shader_st* const ret = calloc(1L, sizeof(shader_st));
    DEBUG("Malloc'd shader_st struct at address %p", ret);
    return ret;
}

void shader_destroy(shader_st *shd){
    assert(shd != NULL);
    DEBUG("Free'd shader_st struct at address %p", shd);
    free(shd);
}

void shader_set_fname(shader_st *shd, const char *fname){
    assert(shd != NULL);
    assert(fname != NULL);

    shd->fname = fname;
}
void shader_set_type(shader_st *shd, GLenum type){
    assert(shd != NULL);

    shd->type = type;
}


char const * shader_get_fname(const shader_st *shd){
    assert(shd != NULL);

    return shd->fname;
}

unsigned int shader_get_id(const shader_st *shd){
    assert(shd != NULL);
    
    return shd->id;
}

error_et shader_readcompile(shader_st* shd){
    size_t shd_src_len;
    char* shd_src_buf;
    if (read_file(shd->fname, &shd_src_buf, &shd_src_len) != CHAUDER_SUCCESS){
        ERROR("Could not read content of file '%s'", shd->fname);
        return SHADER_READ_ERROR;
    }   

    GLint res = GL_FALSE;
    int log_len;

    // Compile shader
    DEBUG("Compiling shader '%s'", shd->fname);
    char const* shd_src = shd_src_buf;
    glShaderSource(shd->id, 1, &shd_src, (int*)&shd_src_len);
    glCompileShader(shd->id);
    free(shd_src_buf);

    // Check Shader
    glGetShaderiv(shd->id, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shd->id, GL_INFO_LOG_LENGTH, &log_len);
    if ( log_len > 0 ){
        char* err_msg = malloc(log_len+1);
        glGetShaderInfoLog(shd->id, log_len, NULL, err_msg);
        err_msg[log_len] = '\0';
        ERROR("%s", err_msg);
        free(err_msg);
        return SHADER_COMPILE_ERROR;
    }
    return CHAUDER_SUCCESS;
}

error_et shader_compile(shader_st *shd){
    assert(shd != NULL);

    shd->id = glCreateShader(shd->type);
    assert(shd->id != 0);

    // Update the modification time of the shader
    struct stat st;
    stat(shd->fname, &st);
    shd->mtime = st.st_mtim;

    return shader_readcompile(shd);
}

bool shader_update(shader_st* shd){
    // This is a user function, it should not be called on shd==NULL 
    // If called on shd==NULL this is a no-op
    if (shd == NULL) return false;

    // Get the last modified time of the file
    struct stat tmp;
    stat(shd->fname, &tmp);
    struct timespec mtime = tmp.st_mtim;
    if (mtime.tv_sec > shd->mtime.tv_sec || 
            (mtime.tv_sec == shd->mtime.tv_sec && mtime.tv_nsec > shd->mtime.tv_nsec )){

        shd->mtime = mtime;
        error_et err = shader_readcompile(shd);
        if (err == CHAUDER_SUCCESS) {
            DEBUG("Successfully updated shader '%s'", shd->fname);
            return true;
        }

        ERROR("Error when trying to update shader '%s'", shd->fname);
    }

    return false;
}
