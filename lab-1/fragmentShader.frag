#version 330

out vec4 FragColor;
in vec4 vColor;
uniform vec4 color;

void main()
{
    FragColor = vColor * color;
}