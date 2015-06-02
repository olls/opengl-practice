#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <stdexcept>


const int WIDTH = 640;
const int HEIGHT = 480;


// Shader sources
const GLchar* vertexSource =
    "#version 150 core\n"

    "in vec2 position;"

    "void main() {"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 150 core\n"

    "out vec4 outColor;"

    "void main() {"
    "   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
    "}";


void glfwHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
}


int loadShaders(GLuint* vertexShader, GLuint* fragmentShader, GLuint* shaderProgram) {
    GLint status;

    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexSource, NULL);
    glCompileShader(*vertexShader);
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        return 0;
    }

    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(*fragmentShader);
    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        return 0;
    }

    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, *vertexShader);
    glAttachShader(*shaderProgram, *fragmentShader);

    glBindFragDataLocation(*shaderProgram, 0, "outColor");
    glLinkProgram(*shaderProgram);
    glUseProgram(*shaderProgram);

    return 1;
}


int main(int argc, char** argv) {

    // Setup Stuff
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwHints();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mah Window!", nullptr, nullptr); // Windowed

    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();


    // Make an object
    float vertices[] = {
         0.0f,  0.5f, // Vertex 1 (X, Y)
         0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Load shaders
    GLuint vertexShader, fragmentShader, shaderProgram;
    loadShaders(&vertexShader, &fragmentShader, &shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    while(!glfwWindowShouldClose(window)) {

        glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
