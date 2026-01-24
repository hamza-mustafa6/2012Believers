#include "Shape.cpp"

/*
    TO RUN:
    In project source folder, open terminal
    > cmake -B build && cmake --build build
    > ./build/bin/main
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 720), "Game 01");
    window.setFramerateLimit(60);

    Shape rect1(sf::Vector2f(100, 100), sf::Vector2i(1, 1), sf::Color::Red, sf::Vector2f(40, 50));
    Shape circ1(sf::Vector2f(120, 120), sf::Vector2i(3, 3), sf::Color::Blue, 20);

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

        rect1.Update(window);
        circ1.Update(window);

        window.clear();

        // Draw here
        rect1.Render(window);
        circ1.Render(window);
        
        window.display();
    }
}
