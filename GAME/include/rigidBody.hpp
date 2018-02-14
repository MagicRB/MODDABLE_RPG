#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "ModdingAPI.hpp"
#include "gameObject.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class modAPI;

class rigid_body
{
    public:

        virtual void on_collided(modAPI* mAPI, gameObject* colliding_game_object) = 0;
        virtual sf::FloatRect get_previous_bounds() = 0;
};

#endif //RIGID_BODY_H
