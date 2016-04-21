
#version 330 core

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPosition;

in vec3 fragNormal;
in vec3 fragPosition;

out vec4 color;
void main(){
    
    float specularStrength = 0.5f;
    float ambientStrength = 0.3f;
    
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow( max( dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    
    color = vec4(result, 1.0f);
}

/*
#version 330 core
in vec3 LightingColor; 

out vec4 color;

uniform vec3 objectColor;

void main()
{
   color = vec4(LightingColor * objectColor, 1.0f);
}
*/