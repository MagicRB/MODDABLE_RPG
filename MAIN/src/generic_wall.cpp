#include "generic_wall.hpp"

#include <iostream>

#include <experimental/filesystem>

generic_wall::generic_wall(modAPI* mAPI, int x, int y)
{
    chunkified_pos<int> ch;

    ch = world_to_chunk(x, y);

    mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y] = this;

    setTilePosition(x, y);

    ch = world_to_chunk(getPosition().x / 32 - 1, getPosition().y / 32);
    if(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y] != NULL) { mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y]->blockUpdate(this); }
    ch = world_to_chunk(getPosition().x / 32 + 1, getPosition().y / 32);
    if(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y] != NULL) { mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y]->blockUpdate(this); }
    ch = world_to_chunk(getPosition().x / 32, getPosition().y / 32 - 1);
    if(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y] != NULL) { mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y]->blockUpdate(this); }
    ch = world_to_chunk(getPosition().x / 32, getPosition().y / 32 + 1);
    if(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y] != NULL) { mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y]->blockUpdate(this); }
    setOrigin(0, 0);
}

generic_wall::~generic_wall()
{

}

sf::FloatRect generic_wall::getBounds()
{
    return getGlobalBounds();
}

void generic_wall::render(sf::RenderWindow* Window)
{
    Window->draw(*this);
}

void generic_wall::interact(gameObject* igom)
{

}

bool generic_wall::collide(gameObject* cgom)
{
    return true;
}

void generic_wall::blockUpdate(gameObject* updater)
{
    chunkified_pos<int> ch;

    bool left = false;
    bool right = false;
    bool top = false;
    bool bottom = false;

    ch = world_to_chunk(getPosition().x / 32 - 1, getPosition().y / 32);
    if (dynamic_cast<generic_wall*>(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y])) { left = true; }
    ch = world_to_chunk(getPosition().x / 32 + 1, getPosition().y / 32);
    if (dynamic_cast<generic_wall*>(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y])) { right = true; }
    ch = world_to_chunk(getPosition().x / 32, getPosition().y / 32 - 1);
    if (dynamic_cast<generic_wall*>(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y])) { top = true; }
    ch = world_to_chunk(getPosition().x / 32, getPosition().y / 32 + 1);
    if (dynamic_cast<generic_wall*>(mAPI->chunks[std::pair<int, int>(ch.chunk_x, ch.chunk_y)].objects[ch.x][ch.y])) { bottom = true; }

    if (bottom && top && !left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_vertical")); }
    else if (!bottom && !top && left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_horizontal")); }
    else if (bottom && !top && left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_corner_top_right")); }
    else if (bottom && !top && !left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_corner_top_left")); }
    else if (!bottom && top && left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_corner_bottom_right")); }
    else if (!bottom && top && !left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_corner_bottom_left")); }
    else if (bottom && top && !left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_t_left")); }
    else if (bottom && top && left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_t_right")); }
    else if (bottom && !top && left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_t_top")); }
    else if (!bottom && top && left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_t_bottom")); }
    else if (bottom && top && left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_cross")); }
    else if (!bottom && !top && !left && right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_end_left")); }
    else if (!bottom && !top && left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_end_right")); }
    else if (!bottom && top && !left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_end_bottom")); }
    else if (bottom && !top && !left && !right) { setTexture(mAPI->textureManager.get()->texture_map.at("wall_end_top")); }
    else { setTexture(mAPI->textureManager.get()->texture_map.at("wall_pillar")); }
}

void generic_wall::setTilePosition(float x, float y)
{
    setPosition(x * 32, y * 32);
}
