#include <SFML/Graphics.hpp>

enum class ShapeType{ SQUARE, CIRCLE, RECTANGLE };

class Shape
{  
    public:
    Shape();
    ~Shape();

    std::string GetString() const;
    sf::Vector2f GetPosition() const;
    sf::Color GetColor() const;
    sf::Vector2i GetSpeed() const;

    void Update();
    private:
    std::string m_name;
    sf::Vector2f m_pos;
    sf::Color m_shapeColor;
    sf::Vector2i m_speed;

    sf::Font m_font;
    sf::Text m_content;
    int m_fontSize;
    sf::Color m_fontColor;

};