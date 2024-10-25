#version 460 core
in vec2 center;
in vec2 position;
out vec4 FragColor;

void main() {

    float r_sqr = dot(position - center, position - center);

    if (r_sqr < 0.25f) FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    else 
        discard;
} 
