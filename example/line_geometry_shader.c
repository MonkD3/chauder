#include <stdio.h>
#include <stdlib.h>
#include "chauder.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(__attribute__((unused)) GLFWwindow* window, int width, int height){ glViewport(0, 0, width, height); }  

int main(int argc, char** argv){
    chauder_init(argc, argv);

    // ============================ OpenGL Context ============================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(3880, 1440, "Hot-reloading shader example", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to initialize window\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    // Automatically resize 
    glfwSetWindowAspectRatio(window, 16, 9);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    printf("Loaded OpenGL %d.%d with GLAD\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // ======================= Shaders and Program ============================
    // Allocate a shader and set its attributes
    shader_st* vshd = shader_new();
    shader_set_type(vshd, GL_VERTEX_SHADER);
    shader_set_fname(vshd, "../assets/vertex/2d_position_shader.vert");

    // Compile the shader
    error_et err = shader_compile(vshd);
    if (err != CHAUDER_SUCCESS) fprintf(stderr, "Failed to compile the vertex shader\n");

    // Do the same for the geometry shader
    shader_st* gshd = shader_new();
    shader_set_type(gshd, GL_GEOMETRY_SHADER);
    shader_set_fname(gshd, "../assets/geometry/2d_point_to_line_triangle_strip.geom");
    err = shader_compile(gshd);
    if (err != CHAUDER_SUCCESS) fprintf(stderr, "Failed to compile the geometry shader\n");

    // Do the same for the fragment shader
    shader_st* fshd = shader_new();
    shader_set_type(fshd, GL_FRAGMENT_SHADER);
    shader_set_fname(fshd, "../assets/fragment/constant_color.frag");
    err = shader_compile(fshd);
    if (err != CHAUDER_SUCCESS) fprintf(stderr, "Failed to compile the fragment shader\n");

    // Create a program
    program_st* prg = program_new();

    // You can add as many shaders as you want
    program_add_shader(prg, vshd);
    program_add_shader(prg, fshd);
    program_add_shader(prg, gshd);

    program_link(prg);
    GLuint prg_id = program_get_id(prg);
    glUseProgram(prg_id);

    // ========================== Object data =================================

    // Only give the center
    float pos[4] = { 
        -0.5f, -0.5f, 
         0.5f,  0.5f 
    };
    
    GLuint vao, vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(float), pos, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // ========================== Rendering Loop ==============================
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_LINES, 0, 2);
        glfwSwapBuffers(window);

        // This will recompile the shaders whenever they are modified ! (try it)
        program_update(prg);
    }

    // Destroy the shader when finished
    shader_destroy(vshd);
    shader_destroy(fshd);
    shader_destroy(gshd);
    program_destroy(prg);

    glfwTerminate();
    chauder_finalize();
    return EXIT_SUCCESS;
}
