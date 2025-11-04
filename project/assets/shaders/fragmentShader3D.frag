#version 460 core

in vec2 TexCoords;

uniform vec4 diffuse;
uniform sampler2D image;

out vec4 fragColor;

void main() {
    fragColor = diffuse * texture(image, TexCoords);
}
