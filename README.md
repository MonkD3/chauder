# Chauder

[ʃo] Chaud (*french, adjective*) : high in temperature. 

Chauder is a library allowing hot-reloading of OpenGL shaders. 

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
