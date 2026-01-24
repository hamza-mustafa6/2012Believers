#include "Shape.cpp"
#include <fstream>
#include <iostream>
#include <sstream>

/*
    TO RUN:
    In project source folder, open terminal
    > cmake -B build && cmake --build build
    > ./build/bin/main
*/

using ShapeList = std::vector<Shape>;

int main()
{
    // Main class variables
    sf::Vector2u windowSize;

    sf::Font font;
    sf::Color textColor;
    int fontSize;

    ShapeList shapeList;

    std::ifstream readConfig("./src/config.txt");
    std::string buffer;

    if (!readConfig.is_open())
    {
        std::cerr << "Could not open file.\n";
        return -1;
    }

    // File reading
    while (std::getline(readConfig, buffer))
    {
        // Skip if line is empty or contains only one character
        if (buffer.empty() || buffer.size() == 1)
        {
            continue;
        }

        // Skip if line is a comment
        if (buffer[0] == '/' && buffer[1] == '/')
        {
            continue;
        }

        std::stringstream readLine(buffer);
        std::string readWord;

        unsigned int windX, windY; // Window size

        std::string fontFile; // font file name
        int textR, textG, textB; // text color values
        int fileFontSize; // font size

        std::string name; // Shape name
        float posX, posY; // Shape position
        float speedX, speedY; // Shape speed
        int shapeR, shapeG, shapeB; // Shape color values
        float sizeX, sizeY, radius; // Shape width, height, and radius

        readLine >> readWord;

        // Assign variables for window params
        if (readWord == "Window")
        {
            readLine >> windX >> windY;
            windowSize = sf::Vector2u(windX, windY);
        }

        // Assign variables for font params
        if (readWord == "Font")
        {
            readLine >> fontFile >> fileFontSize >> textR >> textG >> textB;

            font.loadFromFile("./src/" + fontFile);
            fontSize = (int)fileFontSize;
            textColor = sf::Color((int)textR, (int)textG, (int)textB);

            Shape::SetupText(font, textColor, fontSize);
        }

        if (readWord == "Circle")
        {
            readLine >> name >> posX >> posY >> speedX >> speedY >> shapeR >> shapeG >> shapeB >> radius;

            // push a new circle to the shapeList vector containing the params read from file
            shapeList.push_back(Shape(name, 
                                      sf::Vector2f((float)posX, (float)posY), 
                                      sf::Vector2f((float)speedX, (float)speedY), 
                                      sf::Color((int)shapeR, (int)shapeG, (int)shapeB), 
                                      (float)radius));
        }

        if (readWord == "Rectangle")
        {
            readLine >> name >> posX >> posY >> speedX >> speedY >> shapeR >> shapeG >> shapeB >> sizeX >> sizeY;
            
            // Push a new rectangle to the shapeList vector containing the params read from file
            shapeList.push_back(Shape(name,
                                      sf::Vector2f((float)posX, (float)posY),
                                      sf::Vector2f((float)speedX, (float)speedY),
                                      sf::Color((int)shapeR, (int)shapeG, (int)shapeB),
                                      sf::Vector2f((float)sizeX, (float)sizeY)));
        }
    }

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Game 01");
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

        // Update all shapes
        for(int i = 0; i < shapeList.size(); i++)
        {
            shapeList[i].Update(window);
        }

        window.clear();

        // Draw all shapes
        for(int i = 0; i< shapeList.size(); i++)
        {
            shapeList[i].Render(window);
        }
        
        window.display();
    }
}
