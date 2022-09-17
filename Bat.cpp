#include "Bat.h"

#define WIDTH 100

Bat::Bat(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(WIDTH, 20));
	m_Shape.setPosition(m_Position);
}

FloatRect Bat::getPosition() { return m_Shape.getGlobalBounds(); }
RectangleShape Bat::getShape() { return m_Shape; }
void Bat::moveLeft() { m_MovingLeft = true; }
void Bat::moveRight() { m_MovingRight = true; }
void Bat::stopLeft() { m_MovingLeft = false; }
void Bat::stopRight() { m_MovingRight = false; }

void Bat::update(Time dt, float screenX)
{
	float testX = (m_MovingLeft) ? m_Position.x - m_Speed * dt.asSeconds() : m_Position.x + m_Speed * dt.asSeconds();
	if (m_MovingLeft && testX >= 0) m_Position.x = testX;
	if (m_MovingRight && testX + WIDTH <= screenX) m_Position.x = testX;
	m_Shape.setPosition(m_Position);
}