#version 330 core

in vec3 normalInterp;
in vec3 vertPos;

out vec4 fragColor;

const vec3 lightPos = vec3(200.0, 500.0, 250.0);
const vec3 ambientColor = vec3(0.3, 0.4, 0.2);
const vec3 diffuseColor = vec3(0.55, 0.66, 0.44);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main() {
    vec3 normal = normalize(normalInterp);
    vec3 lightDir = normalize(lightPos - vertPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(-vertPos);
    
    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;
    
    if(lambertian > 0.0) {
        float specAngle = max(dot(reflectDir, viewDir), 0.0);
        specular = pow(specAngle, 2.0);
    }

    fragColor = vec4(ambientColor + lambertian*diffuseColor + specular*specColor, 1.0);
    
}
