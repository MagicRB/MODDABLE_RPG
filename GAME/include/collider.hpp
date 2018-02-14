#ifndef COLLIDER_H
#define COLLIDER_H

#include "gameObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class collider
{
    public:
        bool physicallyBlock;

        virtual void on_collide_with(gameObject* collingGameObject) = 0;
};

#endif //COLLIDER_H
