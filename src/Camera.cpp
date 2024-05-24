#include "include/Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
  Camera::width = width;
  Camera::height = height;
  Position = position;
}

  void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
  // Initializes matrices since otherwise they will be the null matrix
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  // Makes camera look in the right direction from the right position
  view = glm::lookAt(Position, Position + Orientation, Up);
  // Adds perspective to the scene
  projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

  // Sets new camera matrix
  cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
  // Exports camera matrix
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    Position += Camera::speed * Camera::Orientation;
  }

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    Position -= Camera::speed * Camera::Orientation;
  }

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    Position += Camera::speed * glm::normalize(glm::cross(Orientation, Up));
  }

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    Position -= Camera::speed * glm::normalize(glm::cross(Orientation, Up));
  }

  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    Position += Camera::speed * Up;
  }

  if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    Position -= Camera::speed * Up;
  }

  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed = 0.4f;
  }

  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed = 0.1f;
  }

  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (firstClick) {
      glfwSetCursorPos(window, (Camera::width / 2), (Camera::height / 2)); // sets cursor to center
      firstClick = false;
    }

    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float rotx = sensitivity * (float)(mouseY - (height / 2)) / height;
    float roty = sensitivity * (float)(mouseX - (width / 2)) / width;

    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, Up)));

    if(!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
      Orientation = newOrientation;
    }

    Orientation = glm::rotate(Orientation, glm::radians(-roty), Up);

    glfwSetCursorPos(window, (Camera::width / 2), (Camera::height / 2));

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
  }
}