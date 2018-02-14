#ifndef GENERIC_WALL_H
#define GENERIC_WALL_H

#include "ModdingAPI.hpp"

#include "gameObject.hpp"
#include "collider.hpp"

class generic_wall : public gameObject, public collider, public sf::Sprite {
public:
    generic_wall(modAPI* mAPI, int x, int y);
    ~generic_wall();

    modAPI* mAPI;

    sf::FloatRect getBounds();
    void render(sf::RenderWindow* Window);
    void interact(gameObject* igom);
    bool collide(gameObject* cgom);
    void blockUpdate(gameObject* updater);

    void on_collide_with(gameObject* collingGameObject);

    void setTilePosition(float x, float y);
protected:

private:

};

#endif // GENERIC_WALL_H
