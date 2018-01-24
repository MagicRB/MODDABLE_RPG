#include "generic_wall.hpp"

#include <iostream>

generic_wall::generic_wall()
{

}

generic_wall::~generic_wall()
{

}

sf::FloatRect generic_wall::getBounds()
{
    return getGlobalBounds();
}

void generic_wall::render(sf::RenderWindow* Window)
{
    Window->draw(*this);
}

void generic_wall::interact(gameObject* igom)
{

}

bool generic_wall::collide(gameObject* cgom)
{
    return true;
}

void generic_wall::blockUpdate(gameObject* updater)
{
    std::cout << "block update" << std::endl;
}

void generic_wall::setTilePosition(float x, float y)
{
    setPosition(x * 32, y * 32);
}
