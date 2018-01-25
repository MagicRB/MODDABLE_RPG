#ifndef GENERIC_WALL_H
#define GENERIC_WALL_H

#include "ModdingAPI.hpp"

#include "gameObject.hpp"

class generic_wall : public gameObject, public sf::Sprite {
public:
    generic_wall(modAPI* mAPI, int x, int y);
    ~generic_wall();

    modAPI* mAPI;

    sf::FloatRect getBounds();
    void render(sf::RenderWindow* Window);
    void interact(gameObject* igom);
    bool collide(gameObject* cgom);
    void blockUpdate(gameObject* updater);

    void setTilePosition(float x, float y);
protected:

private:

};

#endif // GENERIC_WALL_H
