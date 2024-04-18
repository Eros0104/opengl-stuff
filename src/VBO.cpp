#include "../include/VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Bind the VBO specifying it's a GL_ARRAY_BUFFER
void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Delete() {
    glDeleteBuffers(1, &ID);
}

// Bind the VBO to 0 so that we don't accidentally modify it
void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}