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

void door::blockUpdate(gameObject* updater)
{

}

door::door()
{
    setOrigin(0,0);
}

door::~door()
{

}
