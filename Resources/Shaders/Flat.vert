#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv; // Unused for this example

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

flat out vec4 faceColor; // flat -> do not interpolate values

void main(void) {
    
    vec3 lightPos = vec3(20.0, 50.0, 15.0);
    vec4 color = vec4(1.0, 0.7, 0.5, 1.0);

    mat4 modelView = view * model;
    mat4 modelViewProjection = projection * modelView;
    
    // Transform the vertex into eye space.
    vec3 modelViewVertex = vec3(modelView * position);
    
    // Transform the normal's orientation into eye space.
    vec3 modelViewNormal = vec3(modelView * vec4(normal, 0.0));
    
    // Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(lightPos - modelViewVertex);
    
    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(modelViewNormal, lightVector), 0.2);
    
    // Multiply the color by the illumination level. It will be interpolated across the triangle.
    faceColor = color * diffuse;
    
    gl_Position = modelViewProjection * position;
}