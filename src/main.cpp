
#include <iostream>
#include "vendors/glad/glad.h"
#include "vendors/GLFW/glfw3.h"

int main(void)
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we want to use the core-profile
    // This means we'll be using only the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    // Check if the window was created successfully
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 800, 600);

    // Tell OpenGL the color of the background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Clear the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // Main while loop
    while(!glfwWindowShouldClose(window))
    {
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    
    return 0;
}