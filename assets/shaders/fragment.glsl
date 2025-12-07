#version 330 core
out vec4 FragColor;

in vec2 vUV;

uniform sampler2D baseColorTxt;

void main() {
    vec4 texColor = texture(baseColorTxt, vUV);
    FragColor = texColor;
}