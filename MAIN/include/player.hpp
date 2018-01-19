#include "gameObject.hpp"
#include "ModdingAPI.hpp"

#include "SFML/Graphics.hpp"


class player : public gameObject, public sf::Sprite
{
    public:

        virtual void render(sf::RenderWindow* Window);
		virtual void interact(gameObject* igom);
        virtual bool collide(gameObject* cgom);
        virtual sf::FloatRect getBounds();

        void updatePosition(modAPI* mAPI);

        void movement(modAPI* mAPI);

        int movement_increment = 3;

        player(modAPI* mAPI);
        ~player();
    protected:

        sf::Texture texture;

    private:
};