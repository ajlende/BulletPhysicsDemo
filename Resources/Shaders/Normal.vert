#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 f_normal;

void main(void) {
    mat4 modelView = view * model;
    mat4 modelViewProjection = projection * modelView;
    f_normal = normal;
    gl_Position = modelViewProjection * vec4(position, 1.0);
}