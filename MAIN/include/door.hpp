#ifndef DOOR_H
#define DOOR_H

#include "gameObject.hpp"

#include <SFML/Graphics.hpp>

class door : public gameObject, public sf::Sprite
{
    public:

        bool open = false;

        virtual void render(sf::RenderWindow* Window);
		virtual void interact(gameObject* igom);
		virtual bool collide(gameObject* cgom);
		virtual sf::FloatRect getBounds();

        void setTilePosition(float x, float y);

        door();
        ~door();

    protected:

    private:
    
};

#endif // DOOR_H