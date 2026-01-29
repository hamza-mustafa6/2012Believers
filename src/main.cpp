#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <vector> 

enum class ShapeType { RECTANGLE, CIRCLE }; // Enum class for shape type flags

/*
    Shape Class Header

    @Author Alex
*/
class Shape
{  
    public:
    // Constructors and Destructor
    Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed, 
          sf::Color l_color, sf::Vector2f l_size);
    Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed,
          sf::Color l_color, float l_radius);
    ~Shape();

    static void SetupText(sf::Font& l_font, sf::Color l_color, int l_size); // Static method to init text params

    void Update(sf::RenderWindow& l_window); // Update shape's position
    void Render(sf::RenderWindow& l_window); // Draw shape to window

    private:

    static sf::Font s_font; // Static font
    static sf::Color s_textColor; // Static text color
    static int s_fontSize; // Static font size

    ShapeType m_shapeType; // Type of shape
    sf::Vector2f m_speed; // Shape Speed

    sf::Text m_content; // Text

    sf::CircleShape m_circle; // Circle drawable object
    sf::RectangleShape m_rect; // Rectangle Drawable object

    void UpdateCircle(sf::Vector2u l_windowSize); // Same as regular Update method, pertains to circles only
    void CreateText(std::string l_string); // Sets the text content of the shape label and sets up proper positioning

};

/*
    Shape Class Methods

    @Author Alex
*/
sf::Font Shape::s_font;
sf::Color Shape::s_textColor;
int Shape::s_fontSize;

// Rectangle Constructor
Shape::Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed, sf::Color l_color, sf::Vector2f l_size)
{
    m_shapeType = ShapeType::RECTANGLE;

    m_rect.setSize(l_size);
    m_rect.setFillColor(l_color);
    m_rect.setPosition(l_position);

    CreateText(l_name);

    m_speed = l_speed;
}
Shape::~Shape() {}

// Circle Constructor
Shape::Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed, sf::Color l_color, float l_radius)
{
    m_shapeType = ShapeType::CIRCLE;

    m_circle.setRadius(l_radius);
    m_circle.setFillColor(l_color);
    m_circle.setPosition(l_position);

    CreateText(l_name);

    m_speed = l_speed;
}

// Static method that sets static text variables
void Shape::SetupText(sf::Font& l_font, sf::Color l_color, int l_size)
{
    s_font = l_font;
    s_textColor = l_color;
    s_fontSize = l_size;
}

// Sets params for drawable text object, and centers its origin point
void Shape::CreateText(std::string l_name)
{
    m_content.setFont(s_font);
    m_content.setCharacterSize(s_fontSize);
    m_content.setFillColor(s_textColor);
    m_content.setString(l_name);

    sf::Vector2f l_localBounds(m_content.getLocalBounds().getSize().x, m_content.getLocalBounds().getSize().y);
    m_content.setOrigin(l_localBounds.x / 2, l_localBounds.y / 2);
}

// Update shape and text position
void Shape::Update(sf::RenderWindow& l_window)
{
    sf::Vector2u l_windowSize = l_window.getSize(); // Get window bounds

    // If the shape type is circle, run the private method UpdateCircle() instead.
    if(m_shapeType == ShapeType::CIRCLE)
    {
        UpdateCircle(l_windowSize);
        return;
    }

    // If the edge of the object crosses window bounds, reverse its movement direction on given axis.
    if (m_rect.getPosition().x > l_windowSize.x - m_rect.getSize().x ||
        m_rect.getPosition().x < 0)
    {
        m_speed.x = -m_speed.x;
    }
    if (m_rect.getPosition().y > l_windowSize.y - m_rect.getSize().y ||
        m_rect.getPosition().y < 0)
    {
        m_speed.y = -m_speed.y;
    }
    
    // Update position by adding m_speed
    m_rect.setPosition
    (
        m_rect.getPosition().x + m_speed.x,
        m_rect.getPosition().y + m_speed.y
    );
    // Update text position to keep it in the center of the shape
    m_content.setPosition(m_rect.getPosition().x + m_rect.getSize().x / 2,
                          m_rect.getPosition().y + m_rect.getSize().y / 2);

}

// Same as Update() but pertains to circle object.
void Shape::UpdateCircle(sf::Vector2u l_windowSize)
{
    // If the edge of the circle crosses window bounds, reverse its movement direction on given axis.
    if (m_circle.getPosition().x > l_windowSize.x - m_circle.getRadius() * 2 ||
        m_circle.getPosition().x < 0)
    {
        m_speed.x = -m_speed.x;
    }
    if (m_circle.getPosition().y > l_windowSize.y - m_circle.getRadius() * 2 ||
        m_circle.getPosition().y < 0)
    {
        m_speed.y = -m_speed.y;
    }

    // Update position by adding m_speed
    m_circle.setPosition
    (
        m_circle.getPosition().x + m_speed.x,
        m_circle.getPosition().y + m_speed.y
    );
    // Update text position to keep it in the center of the shape
    m_content.setPosition(m_circle.getPosition().x + m_circle.getRadius(),
                          m_circle.getPosition().y + m_circle.getRadius());
}

// Draw shape and text to window.
void Shape::Render(sf::RenderWindow& l_window)
{
    // If shape type is rectangle, draw m_rect, otherwise draw m_circle
    if (m_shapeType == ShapeType::RECTANGLE)
    {
        l_window.draw(m_rect);
    }
    else
    {
        l_window.draw(m_circle);
    }
    
    // Draw text
    l_window.draw(m_content);
}

/*
    TO RUN:
    In project source folder, open terminal
    > cmake -B build && cmake --build build
    > ./build/bin/main
*/

int main()
{
    // variables 
    // window 
    unsigned int windowWidth;
    unsigned int windowHeight;
    // font 
    unsigned int fontSize;
    unsigned int R, G, B;
    sf::Font font;
    std::string fontName; 
    // shapes
    std::string shapeName;
    float posX;
    float posY;
    float speedX;
    float speedY;
    float radius;
    float rectangleWidth;
    float rectangleHeight; 
    std::vector<Shape> shapes; // makes shapes vector 

    // open config.txt and pass the fle path into the constructor 
    std::ifstream ConfigFile("./src/config.txt");
    std::string text;
    
    // close program if cannot find config file 
    if(!ConfigFile.is_open())
    {
        std::cerr << "Could not open config file. \n";
        return -1; 
    }

    // reading the config file
    while(std::getline(ConfigFile, text))
    {
        // if the text is space or // skip 
        // if 'Window' set window width and height 
        // if 'Circle' set circle parameters 
        // if 'Rectangle' set rectangle parameters 

        // if a space of a comment, skip 
        if(text.empty() || text[0] == '/')
        {
            continue;
        }

        // window width and height 
        std::istringstream iss(text); // 
        std::string type;
        iss >> type; // >> skips whitespace / tabs and reads chars until tab. auto converts to target type 

        if(type == "Window")
        {
            iss >> windowWidth;
            iss >> windowHeight; 
            // can also write iss >> windowWidth >> windowHeight. can chain. 
        }

        
        if(type == "Font")
        {
            iss >> fontName;
            iss >> fontSize;
            iss >> R >> G >> B; 
            // Load font and set up static text parameters immediately
            if (!font.loadFromFile("./src/" + fontName))
            {
                std::cerr << "Failed to load font: " << fontName << "\n";
            }
            Shape::SetupText(font, sf::Color(R, G, B), fontSize);
        }

        // every time there's a 'Circle', it adds a new shape 
        if(type == "Circle")
        {
            iss >> shapeName >> posX >> posY >> speedX >> speedY >> R >> G >> B >> radius;

            shapes.push_back(Shape(shapeName, sf::Vector2f(posX, posY), sf::Vector2f(speedX, speedY), sf::Color(R, G, B), radius));

        }

        if(type == "Rectangle")
        {
            iss >> shapeName >> posX >> posY >> speedX >> speedY >> R >> G >> B >> rectangleWidth >> rectangleHeight;

            shapes.push_back(Shape(shapeName, sf::Vector2f(posX, posY), sf::Vector2f(speedX, speedY), sf::Color(R, G, B), sf::Vector2f(rectangleWidth, rectangleHeight)));

        }
        

    }

    // window size 
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game 01");
    window.setFramerateLimit(60);


    // IMPORTANT!!! the static method SetupText() NEEDS to be run BEFORE any shape objects are instantiated, otherwise text will not work.

    /*
        Shape constructor guide:

        Shape shapeName(name, position float vector, speed float vector, color object, size float vector)  For Rectangle
        Shape shapeName(name, position float vector, speed float vector, color object, radius float value) For Circle

        The constructor is overloaded so it will automatically make a rect or a circle depending on whether you pass it a float vector or a single float.
    */



    // rectangles 
    // Shape rect1("Rectangle", sf::Vector2f(100, 100), sf::Vector2f(-2, 2), sf::Color(255, 0, 0), sf::Vector2f(100, 100));

    // circles 
    // Shape circ1("Circle", sf::Vector2f(100, 100), sf::Vector2f(3, -4), sf::Color(0, 0, 255), 100);

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

        // rect1.Update(window);
        // circ1.Update(window);

        // Draw here
        // rect1.Render(window);
        // circ1.Render(window);

        window.clear();
        for(auto& shape : shapes)
        {
            shape.Update(window);
            shape.Render(window);
        }

        window.display();
    }
}
