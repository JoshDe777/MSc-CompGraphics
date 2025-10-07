#version 330

layout (location = 0) in vec3 aPos;
uniform mat4 mvp;
in vec4 v_color;
out vec4 vColor;

void main() {
    gl_Position = vec4(aPos.xyz, 1.0);
    vColor = v_color;
}