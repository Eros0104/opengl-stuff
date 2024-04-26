// This file is written with GLSL an OpenGL Shading Language
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;

// Outputs the color for the Fragment Shader
out vec3 color;

out vec2 texCoord;

uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  // Outputs the positions/coordinates of all vertices
  gl_Position = proj * view * model * vec4(aPos, 1.0);
  // Assigns the color from the vertex to "color"
  color = aColor;
  texCoord = aText;
}