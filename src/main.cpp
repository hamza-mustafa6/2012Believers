#include <SFML/Graphics.hpp>

/*
    TO RUN:
    In project source folder, open terminal
    > cmake -B build && cmake --build build
    > ./build/bin/main
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "First Window");
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                // Close window button clicked
                window.close();
            }
        }

        window.clear(sf::Color::Red);

        // Draw here
        
        window.display();
    }
}
