#include "gameObject.hpp"
#include "ModdingAPI.hpp"

#include "SFML/Graphics.hpp"


class player : public gameObject, public sf::Sprite
{
    public:

        void render(sf::RenderWindow* Window);
		void interact(gameObject* igom);
        bool collide(gameObject* cgom);
        sf::FloatRect getBounds();
        void blockUpdate(gameObject* updater);

        void updatePosition(modAPI* mAPI);

        void movement(modAPI* mAPI);

        int movement_increment = 3;

        player(modAPI* mAPI);
        ~player();
    protected:

        sf::Texture texture;

    private:
};
