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
in vec3 color;

out vec3 Color;

void main()
{
    Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}

)glsl";

const GLchar* fragmentSource = R"glsl(

#version 150 core

uniform vec3 multiplier;
in vec3 Color;

out vec4 outColor;

void main()
{
    outColor = vec4(Color.r*multiplier.r, Color.g*multiplier.g, Color.b*multiplier.b, 1.0);  
/*    outColor = vec4((Color.r*multiplier.r + Color.g*multiplier.g + Color.b*multiplier.b) / 3.0,  
                    (Color.r*multiplier.r + Color.g*multiplier.g + Color.b*multiplier.b) / 3.0,  
                    (Color.r*multiplier.r + Color.g*multiplier.g + Color.b*multiplier.b) / 3.0,  
                    1.0);
*/
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
    std::cout << "Hello, World!!" << std::endl;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode(800, 600, 32), "untitled", sf::Style::Resize, settings);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    glewExperimental = GL_TRUE;
    glewInit();
    
    float myVertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // Bottom-left
    };

    GLuint myVBO;
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myVertices), myVertices, GL_STATIC_DRAW);

     GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    GLuint myEBO;
    glGenBuffers(1, &myEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

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
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(myProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    GLint uniMul = glGetUniformLocation(myProgram, "multiplier");
    glUniform3f(uniMul, 0.33f, 0.33f, 0.33f);

    int i = 0;
    bool running = true;
    while (running) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                running = false;                
            }
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        i+=2; 
        glUniform3f(uniMul, 0.5+0.5*cos(i*M_PI/180), 0.5+0.5*cos(i*M_PI/180), 0.5+0.5*cos(i*M_PI/180));

        window.display();
    }

    glDeleteProgram(myProgram);
    glDeleteShader(myFragmentShader);
    glDeleteShader(myVertexShader);

    glDeleteBuffers(1, &myEBO);
    glDeleteBuffers(1, &myVBO);

    window.close();
    return 0;
}

