#include "player.hpp"

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

void player::updatePosition(modAPI* mAPI)
{
    mAPI->view.get()->setCenter(sf::Vector2f(position.x, position.y));
    setPosition(position.x, position.y);
    mAPI->window.get()->setView(*mAPI->view.get());
}

void player::movement(modAPI* mAPI)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.y -= movement_increment;
        updatePosition(mAPI);
        for (int i = 0; i < mAPI->gameObjectManager.get()->go_vector.size(); i++) {
            if (mAPI->gameObjectManager.get()->go_vector.at(i).get() != this)
            {
                found = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->gameObjectManager.get()->go_vector.at(i)->collide(this);
                    if (collide) {
                        position.y += movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = this->getBounds().top - (mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().top + mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().height);

                        position.y -= movement_increment_current;
                    }
                }
            }
        }
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.y += movement_increment;
        updatePosition(mAPI);
        for (int i = 0; i < mAPI->gameObjectManager.get()->go_vector.size(); i++) {
            if (mAPI->gameObjectManager.get()->go_vector.at(i).get() != this)
            {
                found = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->gameObjectManager.get()->go_vector.at(i)->collide(this);
                    if (collide)
                    {
                        position.y -= movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().top - (this->getBounds().top + this->getBounds().height);

                        position.y += movement_increment_current;
                    }
                }
            }
        }
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.x -= movement_increment;
        updatePosition(mAPI);
        for (int i = 0; i < mAPI->gameObjectManager.get()->go_vector.size(); i++) {
            if (mAPI->gameObjectManager.get()->go_vector.at(i).get() != this)
            {
                found = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->gameObjectManager.get()->go_vector.at(i)->collide(this);
                    if (collide) {
                        position.x += movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current =  this->getBounds().left - (mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().left + mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().width);

                        position.x -= movement_increment_current;
                    }
                }
            }
        }
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.x += movement_increment;
        updatePosition(mAPI);
        for (int i = 0; i < mAPI->gameObjectManager.get()->go_vector.size(); i++) {
            if (mAPI->gameObjectManager.get()->go_vector.at(i).get() != this)
            {
                found = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->gameObjectManager.get()->go_vector.at(i)->collide(this);
                    if (collide)
                    {
                        position.x -= movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().left - (this->getBounds().left + this->getBounds().width);

                        position.x += movement_increment_current;
                    }
                }
            }
        }
    }
    updatePosition(mAPI);
}

player::player(modAPI* mAPI)
{
    setOrigin(sf::Vector2f(16, 16));
    texture.loadFromFile("Textures/wall_horizontal.png");
    setTexture(texture);
    setScale(sf::Vector2f(0.8, 0.8));
    position.y += 64;
    mAPI->inputE.add_event([this](modAPI* mAPI){this->movement(mAPI);});
}

player::~player()
{

}
