#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

enum class ShapeType { RECTANGLE, CIRCLE }; // Enum class for shape type flags

// Shape Class Header -------------------------------------------------------------------------------------------------
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
    void UpdateFont();

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
    Shape Class Methods ----------------------------------------------------------------------------------------------
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

    // Text::getLocalBounds returns a Rectangle object outlining the bounds of the text object's content. We can use this to center its origin as we would a normal rectangle.
    sf::Vector2f l_localBounds(m_content.getLocalBounds().getSize().x, m_content.getLocalBounds().getSize().y);
    m_content.setOrigin(l_localBounds.x / 2, l_localBounds.y / 2);
}

void Shape::UpdateFont()
{
    CreateText(m_content.getString());
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

using ShapeList = std::vector<Shape>;

// Main Class --------------------------------------------------------------------------------------------------------------
int main()
{
    // Main class variables
    sf::Vector2u windowSize;

    std::string filePathPrefix = ""; // Assumed prefix for file loading

    sf::Font font;
    sf::Color textColor;
    int fontSize;
    bool fontLoadedLast = false; // Flag for if shapes are initialized before the font

    ShapeList shapeList;

    std::ifstream readConfig(filePathPrefix + "config.txt");
    std::string buffer;

    // Close program if unable to find or open config
    if (!readConfig.is_open())
    {
        std::cerr << "Could not open config file.\n";
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

        std::stringstream readLine(buffer); // converts buffer line to an output stream
        std::string readWord; // buffer for output

        unsigned int windX, windY; // Window size

        std::string fontFile; // font file name
        int textR, textG, textB; // text color values
        int fileFontSize; // font size

        std::string name; // Shape name
        float posX, posY; // Shape position
        float speedX, speedY; // Shape speed
        int shapeR, shapeG, shapeB; // Shape color values
        float sizeX, sizeY, radius; // Shape width, height, and radius

        readLine >> readWord; // Read first word in current line

        // Assign variables for window params
        if (readWord == "Window")
        {
            readLine >> windX >> windY;
            windowSize = sf::Vector2u(windX, windY);
        }

        // Assign variables for font params
        if (readWord == "Font")
        {

            // If the list of shapes already has objects in it, then we know the font is being loaded after shapes have been initialized
            if (shapeList.size() != 0)
            {
                fontLoadedLast = true;
            }
            // Assign the next words in the line in a sequence to local variables
            readLine >> fontFile >> fileFontSize >> textR >> textG >> textB;

            // Set up font params
            if (!font.loadFromFile(filePathPrefix + fontFile))
            {
                std::cout << "Unable to load font";
                return -1;
            }
            fontSize = (int)fileFontSize;
            textColor = sf::Color((int)textR, (int)textG, (int)textB);

            // Call the Shape class text "constructor" method
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

    readConfig.close();

    // If the font info was listed after the shape info, each shape needs to have its text reinitialized
    if (fontLoadedLast)
    {
        for(int i = 0; i < shapeList.size(); i++)
        {
            shapeList[i].UpdateFont();
        }
    }
    

    // Set up window and framerate
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Game 01");
    window.setFramerateLimit(60);
    
    // Main loop
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