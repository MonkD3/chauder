#version 460 core
layout (location = 0) in vec2 vPos; 

void main(){
    gl_Position = vec4(vPos.xy, 0.0f, 1.0f);
}
