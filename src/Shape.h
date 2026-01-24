#include <SFML/Graphics.hpp>

enum class ShapeType { RECTANGLE, CIRCLE };

// TODO: The class needs access to creating fonts and whatnot

class Shape
{  
    public:

    Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed, 
          sf::Color l_color, sf::Vector2f l_size);
    Shape(std::string l_name, sf::Vector2f l_position, sf::Vector2f l_speed,
          sf::Color l_color, float l_radius);
    ~Shape();

    static void SetupText(sf::Font& l_font, sf::Color l_color, int l_size);

    void Update(sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);

    private:

    static sf::Font s_font; // Static font
    static sf::Color s_textColor; // Static text color
    static int s_fontSize; // Static font size

    ShapeType m_shapeType; // Type of shape
    sf::Vector2f m_speed; // Shape Speed

    sf::Text m_content; // Text

    sf::CircleShape m_circle; // Circle drawable object
    sf::RectangleShape m_rect; // Rectangle Drawable object

    void UpdateCircle(sf::Vector2u l_windowSize);
    void CreateText(std::string l_string);

};