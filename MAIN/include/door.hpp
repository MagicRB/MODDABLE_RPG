#ifndef DOOR_H
#define DOOR_H

#include "gameObject.hpp"

#include <SFML/Graphics.hpp>

class door : public gameObject, public sf::Sprite
{
    public:

        bool open = false;

        void render(sf::RenderWindow* Window);
		void interact(gameObject* igom);
		bool collide(gameObject* cgom);
		sf::FloatRect getBounds();
		void blockUpdate(gameObject* updater);

        void setTilePosition(float x, float y);

        door();
        ~door();

    protected:

    private:

};

#endif // DOOR_H
