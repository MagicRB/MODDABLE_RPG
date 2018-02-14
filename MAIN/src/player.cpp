#include "player.hpp"

#include <cmath>
#include <iostream>

void player::render(sf::RenderWindow* Window)
{
    Window->draw(*this);
}

void player::interact(gameObject* igom)
{

}

bool player::collide(gameObject* cgom)
{

}

sf::FloatRect player::getBounds()
{
    return getGlobalBounds();
}

void player::blockUpdate(gameObject* updater)
{

}

void player::on_collided(modAPI* mAPI, gameObject* colliding_game_object)
{
    int dirX = getBounds().left - get_previous_bounds().left;
    int dirY = getBounds().top - get_previous_bounds().top;

    if (dirX > 0) {

        position.x -= getBounds().left + getBounds().width - colliding_game_object->getBounds().left;

    } else if (dirX < 0) {



    } if (dirY > 0 ) {



    } else if (dirY < 0) {



    }

    updatePosition(mAPI);
}

void player::updatePosition(modAPI* mAPI)
{
    previous_bounds = getGlobalBounds();

    mAPI->view.get()->setCenter(sf::Vector2f(position.x, position.y));
    setPosition(position.x, position.y);
    mAPI->window.get()->setView(*mAPI->view.get());
}

void player::movement(modAPI* mAPI)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        position.y -= movement_increment;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        position.y += movement_increment;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        position.x -= movement_increment;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        position.x += movement_increment;
    }
    updatePosition(mAPI);
}

sf::FloatRect player::get_previous_bounds()
{
    return previous_bounds;
}

player::player(modAPI* mAPI)
{
    setOrigin(sf::Vector2f(16, 16));
    texture.loadFromFile("Textures/wall_horizontal.png");
    setTexture(texture);
    setScale(sf::Vector2f(1, 1));
    position.y += 64;
    mAPI->inputE.add_event([this](modAPI* mAPI){this->movement(mAPI);});
}

player::~player()
{

}
