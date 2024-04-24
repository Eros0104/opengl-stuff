#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "../vendors/glad/glad.h"

// EBO stands for Element Buffer Objects
// It stores indices that OpenGL uses to decide what vertices to draw
class EBO {
  public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
