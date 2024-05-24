
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "include/shaderClass.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/EBO.h"
#include "include/Texture.h"
#include "include/Camera.h"

const int width = 800;
const int height = 600;

GLfloat vertices[] = {
    // Coordinates          | Colors               | Textures       | Normals  
    // FRONT FACE             
    -0.5f, -0.5f,  0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      0.0f, 0.5f, 0.8f,  // Lower left corner
    -0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      0.0f, 0.5f, 0.8f,  // Upper left corner
     0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      0.0f, 0.5f, 0.8f,  // Upper right corner
     0.5f, -0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      0.0f, 0.5f, 0.8f,  // Lower right corner
         
    // BACK FACE             
    -0.5f, -0.5f, -0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      0.0f, 0.5f, -0.8f,  // Lower left corner
    -0.5f,  0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      0.0f, 0.5f, -0.8f,  // Upper left corner
     0.5f,  0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      0.0f, 0.5f, -0.8f,  // Upper right corner
     0.5f, -0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      0.0f, 0.5f, -0.8f,  // Lower right corner
         
    // LEFT FACE             
    -0.5f, -0.5f, -0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      -0.8f, 0.5f, 0.0f,  // Lower left corner
    -0.5f,  0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      -0.8f, 0.5f, 0.0f,  // Upper left corner
    -0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      -0.8f, 0.5f, 0.0f,  // Upper right corner
    -0.5f, -0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      -0.8f, 0.5f, 0.0f,  // Lower right corner
         
    // RIGHT FACE             
     0.5f, -0.5f, -0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      0.8f, 0.5f, 0.0f,  // Lower left corner
     0.5f,  0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      0.8f, 0.5f, 0.0f,  // Upper left corner
     0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      0.8f, 0.5f, 0.0f,  // Upper right corner
     0.5f, -0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      0.8f, 0.5f, 0.0f,  // Lower right corner
         
    // TOP FACE             
    -0.5f,  0.5f, -0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      0.0f, 1.0f, 0.0f,  // Lower left corner
    -0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      0.0f, 1.0f, 0.0f,  // Upper left corner
     0.5f,  0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      0.0f, 1.0f, 0.0f,  // Upper right corner
     0.5f,  0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      0.0f, 1.0f, 0.0f,  // Lower right corner
         
    // BOTTOM FACE             
    -0.5f, -0.5f, -0.5f,    0.8f, 0.3f, 0.02f,     0.0f, 0.0f,      0.0f, -1.0f, 0.0f,  // Lower left corner
    -0.5f, -0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      0.0f, 1.0f,      0.0f, -1.0f, 0.0f,  // Upper left corner
     0.5f, -0.5f,  0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 1.0f,      0.0f, -1.0f, 0.0f,  // Upper right corner
     0.5f, -0.5f, -0.5f,    0.0f, 0.6f, 1.0f,      1.0f, 0.0f,      0.0f, -1.0f, 0.0f,  // Lower right corner
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
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};


GLfloat lightVertices[] = {
    // Coordinates
    -0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();



    // Shader for light cube
	Shader lightShader("./src/shaders/light.vert", "./src/shaders/light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


    glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.75f, 0.75f, 0.75f);
    glm::vec3 lightScale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, lightScale);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

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

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        // Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        // Export the camMatrix to the Vertex Shader of the pyramid
        camera.Matrix(shaderProgram, "camMatrix");

        // Binds texture so that is appears in rendering
        texture.Bind();
        
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);



        // Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);



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
    lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}
