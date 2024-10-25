#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 position;
out vec2 center;

void main() {    
    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, -0.5f, 0.0f, 0.0f);
    center = gl_in[0].gl_Position.xy;
    position = gl_Position.xy;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5f, 0.0f, 0.0f); 
    center = gl_in[0].gl_Position.xy;
    position = gl_Position.xy;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.5f, 0.5f, 0.0f, 0.0f);
    center = gl_in[0].gl_Position.xy;
    position = gl_Position.xy;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.5f, 0.5f, 0.0f, 0.0f);
    center = gl_in[0].gl_Position.xy;
    position = gl_Position.xy;
    EmitVertex();
    
    EndPrimitive();
} 
