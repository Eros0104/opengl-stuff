// This file is written with GLSL an OpenGL Shading Language
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

// Outputs the color for the Fragment Shader
out vec3 color;

out vec2 texCoord;

out vec3 Normal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main() {
  crntPos = vec3(model* vec4(aPos, 1.0f));

  // Outputs the positions/coordinates of all vertices
  gl_Position = camMatrix * vec4(crntPos, 1.0);
  // Assigns the color from the vertex to "color"
  color = aColor;
  // Assign the texture coordinates from the VertexData to "texCoord"
  texCoord = aTex;
  Normal = aNormal;
}