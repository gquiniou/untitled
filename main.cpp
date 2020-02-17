#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


int main() {
    std::cout << "Hello, World!" << std::endl;


    sf::RenderWindow window(sf::VideoMode(800, 600), "untitled", sf::Style::Close);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    window.display();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
        return 0;
}
