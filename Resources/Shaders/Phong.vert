#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv; // Unused for this example

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normalInterp;
out vec3 vertPos;

void main(void) {
    mat4 modelView = view * model;
    mat4 normalMat = inverse(modelView);
    
    vec4 vertPos4 = modelView * position;
    vertPos = vec3(vertPos4) / vertPos4.w;
    
    normalInterp = vec3(normalMat * vec4(normal, 0.0));
    
    gl_Position = projection * modelView * position;
}