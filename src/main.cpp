#include "Shape.cpp"

/*
    TO RUN:
    In project source folder, open terminal
    > cmake -B build && cmake --build build
    > ./build/bin/main
*/

int main()
{

    // Main class variables
    sf::Vector2u windowSize(800, 600);

    sf::Font font;
    sf::Color textColor = sf::Color(255, 255, 255);
    int fontSize = 18;

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Game 01");
    window.setFramerateLimit(60);

    font.loadFromFile("./src/montserrat.ttf");

    Shape::SetupText(font, textColor, fontSize);

    // Circles
    Shape circ1("CirGreen", sf::Vector2f(100, 100), sf::Vector2f(-3, 2), sf::Color(0, 255, 0), 50);
    Shape circ2("CirBlue", sf::Vector2f(200, 200), sf::Vector2f(2, 4), sf::Color(0, 0, 255), 100);
    Shape circ3("CirPurple", sf::Vector2f(300, 300), sf::Vector2f(-2, -1), sf::Color(255, 0, 255), 75);

    // Rectangles
    Shape rect1("RecRed", sf::Vector2f(200, 200), sf::Vector2f(0.1f, 0.15f), sf::Color(255, 0, 0), sf::Vector2f(100, 45));
    Shape rect2("RecGray", sf::Vector2f(300, 250), sf::Vector2f(-2, 2), sf::Color(100, 100, 100), sf::Vector2f(80, 120));
    Shape rect3("RecCyan", sf::Vector2f(25, 100), sf::Vector2f(-2, -2), sf::Color(0, 255, 255), sf::Vector2f(100, 100));
    
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

        circ1.Update(window);
        circ2.Update(window);
        circ3.Update(window);

        rect1.Update(window);
        rect2.Update(window);
        rect3.Update(window);

        window.clear();

        // Draw here
        rect1.Render(window);
        rect2.Render(window);
        rect3.Render(window);

        circ1.Render(window);
        circ2.Render(window);
        circ3.Render(window);
        
        window.display();
    }
}
