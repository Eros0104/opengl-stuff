// This file is written with GLSL an OpenGL Shading Language
#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

uniform vec4 lightColor;

void main() {
  // FragColor = vec4(color, 1.0f);
  FragColor = texture(tex0, texCoord) * lightColor;
}