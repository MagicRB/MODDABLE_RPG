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
    int x1;
    int x2;
    int y1;
    int y2;
    int x;
    int y;


    x1 = colliding_game_object->getBounds().left +  colliding_game_object->getBounds().width - this->getBounds().left;
    x2 = this->getBounds().left +  this->getBounds().width - colliding_game_object->getBounds().left;

    y1 = colliding_game_object->getBounds().top +  colliding_game_object->getBounds().height - this->getBounds().top;
    y2 = this->getBounds().top +  this->getBounds().height - colliding_game_object->getBounds().top;

    if (abs(x1) < abs(x2))
        x = x1;
    else if (abs(x2) < abs(x1))
        x = x2;

    if (abs(y1) < abs(y2))
        y = y1;
    else if (abs(y2) < abs(y1))
        y = y2;


//    if (abs(x) < abs(y))
//        this->position.x += x;
//    else if (abs(y) < abs(x))
//        this->position.y += y;
//    else {
//        this->position.y += y;
//        this->position.x += x;
//    }

//    std::cout << x1 << ";" << x2 << "    " << y1 << ";" << y2 << std::endl;
    std::cout << x << "    " << y << std::endl;

    updatePosition(mAPI);
}

void player::updatePosition(modAPI* mAPI)
{
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
