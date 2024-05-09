#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../vendors/glm/glm.hpp"
#include "../vendors/glm/gtc/matrix_transform.hpp"
#include "../vendors/glm/gtc/type_ptr.hpp"
#include "../vendors/glm/gtx/rotate_vector.hpp"
#include "../vendors/glm/gtx/vector_angle.hpp"

#include "shaderClass.h"

class Camera {
  public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float speed = 0.1f;
    float sensitivity = 100.0f;

    Camera(int width, int height, glm::vec3 position);

    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};

#endif