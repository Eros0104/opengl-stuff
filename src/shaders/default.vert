// This file is written with GLSL an OpenGL Shading Language
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Outputs the color for the Fragment Shader
out vec3 color;

uniform float scale;

void main() {
  gl_Position = vec4(
    aPos.x + aPos.x * scale, 
    aPos.y + aPos.y * scale, 
    aPos.z + aPos.z * scale, 
    1.0
  );
  // Assigns the color from the vertex to "color"
  color = aColor;
}