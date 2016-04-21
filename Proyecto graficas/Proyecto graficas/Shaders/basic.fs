#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

out vec4 color;
void main(){
    
    vec4 sampledColor1 = texture(Texture1, TexCoord);
    vec4 sampledColor2 = texture(Texture2, TexCoord);
    color = mix(sampledColor1, sampledColor2, 0.6);
}