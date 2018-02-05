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
        position.y -= movement_increment;

        updatePosition(mAPI);

        chunkified_pos<int> ch = world_to_chunk(mAPI->view.get()->getCenter().x / 32, mAPI->view.get()->getCenter().y / 32);

        for (int x = ch.chunk_x - 1; x <= ch.chunk_x + 1; x++)
        for (int y = ch.chunk_y - 1; y <= ch.chunk_y + 1; y++)
        for (int px = 0; px < 64; px++)
        for (int py = 0; py < 64; py++)
        {
            if (mAPI->chunks.count({x, y}) != 0)
            {
                auto& chunk = mAPI->chunks[{x, y}];
                auto* object = chunk.objects[px][py];

                if (object && object != this
                    && object->getBounds().intersects(getGlobalBounds()) // is found
                    && object->collide(this) // collides
                )
                {
                    position.y += movement_increment;

                    updatePosition(mAPI);

                    int movement_increment_current = this->getBounds().top - (object->getBounds().top + object->getBounds().height);
                    position.y -= movement_increment_current;
                }
            }
        }
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        bool collide;
        bool found;
        int movement_increment_current;
        position.y += movement_increment;
        updatePosition(mAPI);
        chunkified_pos<int> ch = world_to_chunk(mAPI->view.get()->getCenter().x / 32, mAPI->view.get()->getCenter().y / 32);
        for (int x = ch.chunk_x - 1; x <= ch.chunk_x + 1; x++) {
            for (int y = ch.chunk_y - 1; y <= ch.chunk_y + 1; y++) {
                for (int px = 0; px < 64; px++) {
                    for (int py = 0; py < 64; py++) {
                        if (mAPI->chunks.count(std::pair<int, int>(x, y)) != 0 && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != NULL && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != this) {
                            found = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().intersects(getGlobalBounds());
                            if (found)
                            {
                                collide = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->collide(this);
                                if (collide) {
                                    position.y -= movement_increment;

                                    updatePosition(mAPI);

                                    movement_increment_current = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().top - (this->getBounds().top + this->getBounds().height);

                                    position.y += movement_increment_current;
                                }
                            }
                        }
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
        chunkified_pos<int> ch = world_to_chunk(mAPI->view.get()->getCenter().x / 32, mAPI->view.get()->getCenter().y / 32);
        for (int x = ch.chunk_x - 1; x <= ch.chunk_x + 1; x++) {
            for (int y = ch.chunk_y - 1; y <= ch.chunk_y + 1; y++) {
                for (int px = 0; px < 64; px++) {
                    for (int py = 0; py < 64; py++) {
                        if (mAPI->chunks.count(std::pair<int, int>(x, y)) != 0 && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != NULL && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != this) {
                            found = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().intersects(getGlobalBounds());
                            if (found)
                            {
                                collide = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->collide(this);
                                if (collide) {
                                    position.x += movement_increment;

                                    updatePosition(mAPI);

                                    movement_increment_current =  this->getBounds().left - (mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().left + mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().width);

                                    position.x -= movement_increment_current;
                                }
                            }
                        }
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
        chunkified_pos<int> ch = world_to_chunk(mAPI->view.get()->getCenter().x / 32, mAPI->view.get()->getCenter().y / 32);
        for (int x = ch.chunk_x - 1; x <= ch.chunk_x + 1; x++) {
            for (int y = ch.chunk_y - 1; y <= ch.chunk_y + 1; y++) {
                for (int px = 0; px < 64; px++) {
                    for (int py = 0; py < 64; py++) {
                        if (mAPI->chunks.count(std::pair<int, int>(x, y)) != 0 && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != NULL && mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py] != this) {
                            found = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().intersects(getGlobalBounds());
                            if (found)
                            {
                                collide = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->collide(this);
                                if (collide) {
                                    position.x -= movement_increment;

                                    updatePosition(mAPI);

                                    movement_increment_current = mAPI->chunks[std::pair<int, int>(x, y)].objects[px][py]->getBounds().left - (this->getBounds().left + this->getBounds().width);

                                    position.x += movement_increment_current;
                                }
                            }
                        }
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
