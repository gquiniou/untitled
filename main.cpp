#include <iostream>
#include <cmath>
#include <string.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

const GLchar* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    }
)glsl";

const GLchar* fragmentSource = R"glsl(
    #version 150 core

    uniform vec3 triangleColor;
    out vec4 outColor;

    void main()
    {
       outColor = vec4(triangleColor, 1.0);
       // outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

void dumpShaderLog(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cout << "Shader compile status: " << status << std::endl;
    }
    const size_t bufsize = 512;
    char buffer[bufsize];
    glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);
    if (strnlen(buffer, bufsize) > 0) {
        std::cout << "Shader compile log: " << std::endl << buffer << std::endl;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode(800, 600, 32), "untitled", sf::Style::Close, settings);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    glewExperimental = GL_TRUE;
    glewInit();
    
    float myVerctices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f,  // Vertex 3 (X, Y)        
    };


    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);

    GLuint myVBO;
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myVerctices), myVerctices, GL_STATIC_DRAW);

    GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(myVertexShader, 1, &vertexSource, nullptr);
    glCompileShader(myVertexShader);
    dumpShaderLog(myVertexShader);

    GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(myFragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(myFragmentShader);
    dumpShaderLog(myFragmentShader);

    GLuint myProgram = glCreateProgram();
    glAttachShader(myProgram, myVertexShader);
    glAttachShader(myProgram, myFragmentShader);
    glBindFragDataLocation(myProgram, 0, "outColor");
    glLinkProgram(myProgram);
    glUseProgram(myProgram);

    GLint posAttrib = glGetAttribLocation(myProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    GLint uniColor = glGetUniformLocation(myProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    int i = 0;
    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

    //glUniform3f(uniColor, 1.0f / (i++%50), 0.0f, 0.0f);
    i+=2; glUniform3f(uniColor, 0.5+0.5*cos(i*M_PI/180), 0.0f, 0.0f);

        window.display();
    }
    return 0;
}

