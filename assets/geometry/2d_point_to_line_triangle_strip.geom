#version 460 core
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

void main() {    

    // Direction and normal
    vec4 d = vec4(normalize((gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy)), 0.0f, 0.0f);
    vec4 n = vec4(vec2(-d.y, d.x), 0.0f, 0.0f);

    // Width
    float w = 0.01f;

    gl_Position = gl_in[0].gl_Position - w*(d + n);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position - w*(d - n);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + w*(d - n);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + w*(d + n);
    EmitVertex();
    
    EndPrimitive();
} 
