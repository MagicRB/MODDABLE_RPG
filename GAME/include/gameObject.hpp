#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class gameObject
{
    public:
        sf::Vector2i position;

        virtual sf::FloatRect getBounds() = 0;
        virtual void render(sf::RenderWindow* Window) = 0;
        virtual void interact(gameObject* igom) = 0;
        virtual bool collide(gameObject* cgom) = 0;
};

#endif //GAME_OBJECT_H