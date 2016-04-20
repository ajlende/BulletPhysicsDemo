#version 330 core

in vec3 f_normal;

out vec4 color;

void main(){
    vec3 N = normalize(f_normal);
    color = vec4((N + vec3(1.0, 1.0, 1.0)) / 2.0,1.0);
}