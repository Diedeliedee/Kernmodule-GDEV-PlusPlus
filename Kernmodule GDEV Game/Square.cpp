#include "SFML/Graphics.hpp"
#include "Shapes.h"

Square::Square(int w, int h)
{
	bounds = Bounds(w, h);
	m_shape.setSize(Vector(w, h).cast());
}

void Square::draw(sf::RenderWindow& window, Vector pos)
{
	m_shape.setPosition(bounds.getOffset(pos, Vector(-1, -1)).cast());
	window.draw(m_shape);
}