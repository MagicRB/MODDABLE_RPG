#include "door.hpp"
#include <iostream>

void door::render(sf::RenderWindow* Window)
{
	Window->draw(*this);
}

void door::interact(gameObject* igom)
{
	open = !open;
}

bool door::collide(gameObject* cgom)
{
	return !open;
}

sf::FloatRect door::getBounds()
{
    return getGlobalBounds();
}

void door::setTilePosition(float x, float y)
{
	setPosition(x * 32, y * 32);
}

door::door()
{
    setOrigin(16,16);
}

door::~door()
{

}
