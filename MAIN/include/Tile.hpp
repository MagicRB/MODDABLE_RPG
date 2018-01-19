#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "gameObject.hpp"

class Tile : public gameObject, public sf::Sprite
{
	public:
		Tile();
		~Tile();

		virtual void render(sf::RenderWindow* Window);
		virtual void interact(gameObject* igom);
		virtual bool collide(gameObject* cgom);
		virtual sf::FloatRect getBounds();

		void setTilePosition(float x, float y);

		bool collidable = false;
	protected:

	private:

};

#endif // TILE_H