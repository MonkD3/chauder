# Chauder

[ʃo] Chaud (*french, adjective*) : high in temperature. 

Chauder is a library allowing hot-reloading of OpenGL shaders with minimal impact on user source code.

This allows user to write OpenGL shaders with live feedback either directly on their application or on a simpler debugging program (as shown in the `examples/`).

It is currently in its alpha stage, modification of its interface are to be expected.

## Dependencies 

* CMake 
* glfw
* glad (included)
* a C compiler

Only tested on linux.

## Compilation

This project uses CMake as its build system. Simply run the following to compile the library as well as the examples :

```bash 
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

And then try executing one of the examples :

```bash 
./example/geometry_shader
```

You should try to modify the corresponding shaders (colors, position ...) with the OpenGL window open to see the rendering change live.
