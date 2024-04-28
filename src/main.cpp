
#include <iostream>
#include "vendors/glad/glad.h"
#include "vendors/GLFW/glfw3.h"
#include "vendors/stb/stb_image.h"
#include "vendors/glm/glm.hpp"
#include "vendors/glm/gtc/matrix_transform.hpp"
#include "vendors/glm/gtc/type_ptr.hpp"
#include "include/shaderClass.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/EBO.h"
#include "include/Texture.h"
#include "include/Camera.h"

const int width = 800;
const int height = 600;

// Triangle vertices coordinates
GLfloat vertices[] = {
    //    Coordinates    |       Colors          |  TEXTURES    // 
    // FRONT
    -0.5f, -0.5f,  0.5f,     0.8f, 0.3f,  0.02f,     0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f,  0.5f,     0.0f, 0.6f,   1.0f,     0.0f, 2.0f, // Upper left
     0.5f,  0.5f,  0.5f,     0.0f, 0.6f,   1.0f,     2.0f, 2.0f, // Upper right
     0.5f, -0.5f,  0.5f,     0.0f, 0.6f,   1.0f,     2.0f, 0.0f, // Lower right corner
    // BACK
    -0.5f, -0.5f, -0.5f,     0.8f, 0.3f,  0.02f,     2.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, -0.5f,     0.0f, 0.6f,   1.0f,     2.0f, 2.0f, // Upper left
     0.5f,  0.5f, -0.5f,     0.0f, 0.6f,   1.0f,     0.0f, 2.0f, // Upper right
     0.5f, -0.5f, -0.5f,     0.0f, 0.6f,   1.0f,     0.0f, 0.0f, // Lower right corner

    // -0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,   0.9f, 0.45f, 0.17f,   0.0f, 0.0f, // Inner left
    //  0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,   0.0f, 0.6f,   1.0f,   0.0f, 0.0f, // Inner right
    //  0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f, 0.3f,  0.02f,   0.0f, 0.0f, // Inner down
};

// Index buffer data
// An index buffer is an array of integers that determines the order in which vertices are drawn
// GLuint indices[] = {
//     0, 3, 5, // Lower left triangle
//     3, 2, 4, // Lower right triangle
//     5, 4, 1 // Upper triangle
// };

GLuint indices[] = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 6, 5,
    4, 7, 6,
    // Left face
    4, 5, 1,
    4, 1, 0,
    // Right face
    3, 2, 6,
    3, 6, 7,
    // Top face
    1, 5, 6,
    1, 6, 2,
    // Bottom face
    0, 3, 7,
    0, 7, 4
};

int main()
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
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

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
    glViewport(0, 0, width, height);

    Shader shaderProgram("./src/shaders/default.vert", "./src/shaders/default.frag");

    // Genereates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets ID of uniform called "scale"
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    Texture texture(
        "./src/textures/monkey.png",
        GL_TEXTURE_2D,
        GL_TEXTURE0,
        GL_RGBA,
        GL_UNSIGNED_BYTE
    );
    texture.texUnit(shaderProgram, "tex0", 0);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main while loop
    while(!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        camera.Inputs(window);

        // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
        glUniform1f(uniID, 0.5f);

        // Binds texture so that is appears in rendering
        texture.Bind();
        
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        //Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texture.Delete();
    shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}
