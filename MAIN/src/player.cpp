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

void player::updatePosition(modAPI* mAPI)
{
    mAPI->grtView()->setCenter(sf::Vector2f(position.x, position.y));
    setPosition(position.x, position.y);
    mAPI->grtWindow()->setView(*mAPI->grtView());
}

void player::movement(modAPI* mAPI)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.y -= movement_increment;
        updatePosition(mAPI);
        for (int i = 0; i < mAPI->grtGom()->go_vector.size(); i++) {
            if (mAPI->grtGom()->go_vector.at(i).get() != this)
            {
                found = mAPI->grtGom()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->grtGom()->go_vector.at(i)->collide(this);
                    if (collide) {
                        position.y += movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = this->getBounds().top - (mAPI->grtGom()->go_vector.at(i)->getBounds().top + mAPI->grtGom()->go_vector.at(i)->getBounds().height);

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
        for (int i = 0; i < mAPI->grtGom()->go_vector.size(); i++) {
            if (mAPI->grtGom()->go_vector.at(i).get() != this)
            {
                found = mAPI->grtGom()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->grtGom()->go_vector.at(i)->collide(this);
                    if (collide)
                    {
                        position.y -= movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = mAPI->grtGom()->go_vector.at(i)->getBounds().top - (this->getBounds().top + this->getBounds().height);

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
        for (int i = 0; i < mAPI->grtGom()->go_vector.size(); i++) {
            if (mAPI->grtGom()->go_vector.at(i).get() != this)
            {
                found = mAPI->grtGom()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->grtGom()->go_vector.at(i)->collide(this);
                    if (collide) {
                        position.x += movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current =  this->getBounds().left - (mAPI->grtGom()->go_vector.at(i)->getBounds().left + mAPI->grtGom()->go_vector.at(i)->getBounds().width);

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
        for (int i = 0; i < mAPI->grtGom()->go_vector.size(); i++) {
            if (mAPI->grtGom()->go_vector.at(i).get() != this)
            {
                found = mAPI->grtGom()->go_vector.at(i)->getBounds().intersects(getGlobalBounds());
                if (found)
                {
                    collide = mAPI->grtGom()->go_vector.at(i)->collide(this);
                    if (collide)
                    {
                        position.x -= movement_increment;

                        updatePosition(mAPI);

                        movement_increment_current = mAPI->grtGom()->go_vector.at(i)->getBounds().left - (this->getBounds().left + this->getBounds().width);

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
    texture.loadFromFile("Textures/stone_wall.png");
    setTexture(texture);
    setScale(sf::Vector2f(0.8, 0.8));
    position.y += 64;
    mAPI->inputE.add_event([this](modAPI* mAPI){this->movement(mAPI);});
}

player::~player()
{

}
