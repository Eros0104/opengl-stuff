// This file is written with GLSL an OpenGL Shading Language
#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;

uniform vec4 lightColor;

uniform vec3 lightPos;

void main() {
  // world base light
  float ambientLight = 0.1f;

  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - crntPos);

  float diffuse = max(dot(normal, lightDirection), 0.0f);

  FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambientLight);
}