#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

const GLchar* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

const GLchar* fragmentSource = R"glsl(
    #version 150 core

    out vec4 outColor;

    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";


int main() {
    std::cout << "Hello, World!" << std::endl;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 2;

    sf::Window window(sf::VideoMode(800, 600, 32), "untitled", sf::Style::Close, settings);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    glewExperimental = GL_TRUE;
    glewInit();
    
    float myVerctices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)        
    };


    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);

    GLuint myBuffer;
    glGenBuffers(1, &myBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, myBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myVerctices), myVerctices, GL_STATIC_DRAW);

    GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(myVertexShader, 1, &vertexSource, nullptr);
    glCompileShader(myVertexShader);
    GLint status;
    glGetShaderiv(myVertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex Shader compile status: " << status << std::endl;
    char buffer[512];
    glGetShaderInfoLog(myVertexShader, sizeof(buffer), nullptr, buffer);
    std::cout << "Vertext shader ompile log: " << buffer << std::endl;


    GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(myFragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(myFragmentShader);
    glGetShaderiv(myVertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment shadder compile status: " << status << std::endl;
    glGetShaderInfoLog(myVertexShader, sizeof(buffer), nullptr, buffer);
    std::cout << "Fragment shader compile log: " << buffer << std::endl;

    GLuint myProgram = glCreateProgram();
    glAttachShader(myProgram, myVertexShader);
    glAttachShader(myProgram, myFragmentShader);
    glBindFragDataLocation(myProgram, 0, "outColor");
    glLinkProgram(myProgram);
    glUseProgram(myProgram);

    GLint posAttrib = glGetAttribLocation(myProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);



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
        //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.display();
    }
    return 0;
}
