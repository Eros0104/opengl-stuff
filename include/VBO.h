#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "../src/vendors/glad/glad.h"

// VBO stands for Vertex Buffer Object
class VBO {
  public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
