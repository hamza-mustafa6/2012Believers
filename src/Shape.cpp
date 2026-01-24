#include "Shape.h"

// @author Alex

// Rectangle/Square constructor
/*
    Takes name, position vector, speed vector, color, and length and width vector
*/
Shape::Shape(sf::Vector2f l_position, sf::Vector2i l_speed, sf::Color l_color, sf::Vector2f l_size)
{
    m_shapeType = ShapeType::RECTANGLE;

    m_rect.setSize(l_size);
    m_rect.setFillColor(l_color);
    m_rect.setPosition(l_position);

    m_speed = l_speed;
}
Shape::~Shape() {}

// Circle Constructor
/*
    Takes name, position vector, speed vector, color, and radius
*/
Shape::Shape(sf::Vector2f l_position, sf::Vector2i l_speed, sf::Color l_color, float l_radius)
{
    m_shapeType = ShapeType::CIRCLE;

    m_circle.setRadius(l_radius);
    m_circle.setFillColor(l_color);
    m_circle.setPosition(l_position);

    m_speed = l_speed;
}

// Sets font member variables
/*
    Takes font, text content, font size, and color
*/
void Shape::CreateText(sf::Font l_font, sf::Text l_content, int l_fontSize, sf::Color l_color)
{
    m_font = l_font;
    m_content = l_content;
    m_fontSize = l_fontSize;
    m_fontColor = l_color;
}

void Shape::Update(sf::RenderWindow& l_window)
{
    sf::Vector2u l_windowSize = l_window.getSize();

    if(m_shapeType == ShapeType::CIRCLE)
    {
        UpdateCircle(l_windowSize);
        return;
    }

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
    
    m_rect.setPosition
    (
        m_rect.getPosition().x + m_speed.x,
        m_rect.getPosition().y + m_speed.y
    );

}

void Shape::UpdateCircle(sf::Vector2u l_windowSize)
{
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

    m_circle.setPosition
    (
        m_circle.getPosition().x + m_speed.x,
        m_circle.getPosition().y + m_speed.y
    );
}

void Shape::Render(sf::RenderWindow& l_window)
{
    if (m_shapeType == ShapeType::RECTANGLE)
    {
        l_window.draw(m_rect);
    }
    else
    {
        l_window.draw(m_circle);
    }
}