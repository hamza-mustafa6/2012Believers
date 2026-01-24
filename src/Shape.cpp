#include "Shape.h"

// @author Alex

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
    
    l_window.draw(m_content);
}