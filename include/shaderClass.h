// This lets c++ know not to open up the file twice, since that would create variable clashes.
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "../src/vendors/glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
  public:
    GLuint ID;
    Shader(const char* vertexFIle, const char* fragmentFile);

    void Activate();
    void Delete();
};

#endif