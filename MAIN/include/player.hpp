#include "gameObject.hpp"
#include "ModdingAPI.hpp"
#include "rigidBody.hpp"

#include "SFML/Graphics.hpp"


class player : public gameObject, public rigid_body, public sf::Sprite
{
    public:

        void render(sf::RenderWindow* Window);
		void interact(gameObject* igom);
        bool collide(gameObject* cgom);
        sf::FloatRect getBounds();
        void blockUpdate(gameObject* updater);
        sf::FloatRect get_previous_bounds();

        void on_collided(modAPI* mAPI, gameObject* colliding_game_object);

        void updatePosition(modAPI* mAPI);

        void movement(modAPI* mAPI);

        int movement_increment = 3;

        sf::FloatRect previous_bounds;

        player(modAPI* mAPI);
        ~player();
    protected:

        sf::Texture texture;

    private:
};
