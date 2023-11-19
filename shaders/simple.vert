#version 400 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

out vec3 fragPos;
out vec3 fragNormal;

void main(void) {
    fragPos = vec3(view * model * vec4(inPosition, 1.0));
    
    mat3 normalMatrix = transpose(inverse(mat3(view * model)));
    fragNormal = normalize(normalMatrix * inNormal);
    
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}