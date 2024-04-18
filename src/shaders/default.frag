// This file is written with GLSL an OpenGL Shading Language
#version 330 core
out vec4 FragColor;

in vec3 color;

void main() {
  FragColor = vec4(color, 1.0f);

}