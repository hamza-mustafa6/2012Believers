#include <SFML/Graphics.hpp>

enum class ShapeType { RECTANGLE, CIRCLE };

// TODO: The class needs access to creating fonts and whatnot

class Shape
{  
    public:
    Shape(sf::Vector2f l_position, sf::Vector2i l_speed, 
          sf::Color l_color, sf::Vector2f l_size);
    Shape(sf::Vector2f l_position, sf::Vector2i l_speed,
          sf::Color l_color, float l_radius);
    ~Shape();

    void Setup(sf::Vector2f l_position, sf::Vector2i l_speed, sf::Color l_color);
    void CreateText(sf::Font l_font, sf::Text l_content, int l_fontSize, sf::Color l_fontColor);

    void Update(sf::RenderWindow& l_window);
    void Render(sf::RenderWindow& l_window);
    private:

    ShapeType m_shapeType; // Type of shape
    sf::Vector2i m_speed; // Shape Speed

    sf::Font m_font; // Font
    sf::Text m_content; // Text
    int m_fontSize; // Size of text
    sf::Color m_fontColor; // Color of text

    sf::CircleShape m_circle;
    sf::RectangleShape m_rect;

    void UpdateCircle(sf::Vector2u l_windowSize);

};