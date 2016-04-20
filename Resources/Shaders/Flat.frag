#version 330 core

flat in vec4 faceColor;

out vec4 color;

void main(){
    color = faceColor;
}