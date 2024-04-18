#include "../include/EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
void EBO::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}

void EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}