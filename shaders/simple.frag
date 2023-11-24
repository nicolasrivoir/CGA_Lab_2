#version 400 core

uniform vec3 baseColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float diffuseCoefficient;
uniform float specularCoefficient;
uniform float specularExponent;
uniform float metalnessFactor;
uniform float gamma;
uniform sampler2D diffuseTexture;
uniform int diffTexEnabled;
uniform sampler2D normalTexture;
uniform int normTexEnabled;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;
in mat3 TBN;

layout(location = 0) out vec4 fragColor;

void main(void) {

	vec3 objectColor = (diffTexEnabled == 1) ? texture(diffuseTexture, fragTexCoord).xyz * baseColor : baseColor;

    // Ambient light
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * objectColor;

    // Diffuse reflection
    vec3 norm = fragNormal;
	if (normTexEnabled == 1) {
		norm = texture(normalTexture, fragTexCoord).xyz;
		norm = norm * 2.0 - 1.0;   
		norm = normalize(TBN * norm);
	}

    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseCoefficient * diff * lightColor;

    // Specular reflection
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);
    vec3 specular = specularCoefficient * spec * mix(lightColor, objectColor, metalnessFactor);

    // Phong reflection (combine previous components)
    vec3 result = (ambient + diffuse) * objectColor + specular;
	
	// Gamma correction (linear to sRGB)
	result = pow(result, vec3(1.0/gamma));
	
    fragColor = vec4(result, 1.0);
}