#version 400 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int normTexEnabled;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 inTangent;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;
out mat3 TBN;

void main(void) {
    fragPos = vec3(view * model * vec4(inPosition, 1.0));
    
    mat3 normalMatrix = transpose(inverse(mat3(view * model)));
    fragNormal = normalize(normalMatrix * inNormal);
	
	fragTexCoord = inTexCoord;
    
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
	
	vec3 tangent = inTangent.xyz;
	vec3 bitangent = cross(inNormal, inTangent.xyz) * inTangent.w;
	
	vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
	vec3 N = normalize(vec3(model * vec4(inNormal,    0.0)));
	vec3 B = cross(N, T);
	TBN = mat3(T, B, N);
}