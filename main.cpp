#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>


int main() {
    std::cout << "Hello, World!" << std::endl;


    sf::RenderWindow window(sf::VideoMode(800, 600), "untitled", sf::Style::Close);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);


    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    printf("%u\n", vertexBuffer);

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            window.display();
        }
    }
    return 0;
}
