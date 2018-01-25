#include "main.h"

#include <iostream>
#include <map>

#include <cmath>

#include <iomanip>
#include "player.hpp"
#include "door.hpp"
#include "generic_wall.hpp"

bool mouse_left_pressed;

player* pl;

std::vector<std::string> split(const char *str, char c = ' ')
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++);

    return result;
}

void controller(modAPI* mAPI, sf::Event event)
{
    if (mAPI->keyBindMap[event.key.code] != NULL && event.type == sf::Event::KeyPressed) {
        mAPI->keyBindMap[event.key.code](mAPI);
    }

    if (mAPI->inputE.get_event_vector().size() != 0) {
        for (unsigned int i = 0; i < mAPI->inputE.get_event_vector().size(); i++) {
            mAPI->inputE.get_event_vector().at(i)(mAPI);
        }
    }

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
        int mouseX = sf::Mouse::getPosition(*mAPI->window.get()).x;
        int mouseY = sf::Mouse::getPosition(*mAPI->window.get()).y;
        sf::Vector2i mouse(mouseX, mouseY);
        if (sqrt( pow(mAPI->window.get()->mapPixelToCoords(mouse).x - pl->getPosition().x, 2) + pow( mAPI->window.get()->mapPixelToCoords(mouse).y - pl->getPosition().y, 2) ) <= 60) {
            for (int i = 0; i < mAPI->gameObjectManager.get()->go_vector.size(); i++) {
                if (mAPI->gameObjectManager.get()->go_vector.at(i)->getBounds().contains(mAPI->window.get()->mapPixelToCoords(mouse))) {
                    mAPI->gameObjectManager.get()->go_vector.at(i)->interact(pl);
                }
            }
        }
    }

    if (event.type == sf::Event::Closed) {
		mAPI->window.get()->close();
		exit(EXIT_SUCCESS);
	} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
		mAPI->window.get()->close();
		exit(EXIT_SUCCESS);
	}
}

void loadFromWorldLine(modAPI* mAPI, std::string line)
{
    int i = 0;

    std::string operation;
    std::string arguments;

    while (line.at(i) != ' ') {
    	operation += line.at(i);
    	i++;
    }
    arguments = line.substr(i + 1, line.size() - 1);

    arguments.erase(std::remove(arguments.begin(), arguments.end(), ' '), arguments.end());

    std::vector<std::string> tokens = split(arguments.c_str(), ';');

    if (operation == ":DOOR") {
    	mAPI->gameObjectManager.get()->go_vector.push_back(std::unique_ptr<gameObject>(new door()));
    	door* d = dynamic_cast<door*>(mAPI->gameObjectManager.get()->go_vector.at(mAPI->gameObjectManager.get()->go_vector.size() - 1).get());
    	d->setTilePosition(atoi(tokens.at(0).c_str()), atoi(tokens.at(1).c_str()));
        mAPI->textureManager.get()->addNewTexture("door");
    	mAPI->textureManager.get()->texture_map.at("door").loadFromFile("Textures/door.png");
    	d->setTexture(mAPI->textureManager.get()->texture_map.at("door"));
    } else if (operation == ":GENERIC_WALL") {
    	mAPI->gameObjectManager.get()->go_vector.push_back(std::unique_ptr<gameObject>(new generic_wall(mAPI, atoi(tokens.at(0).c_str()), atoi(tokens.at(1).c_str()))));
    	generic_wall* w = dynamic_cast<generic_wall*>(mAPI->gameObjectManager.get()->go_vector.at(mAPI->gameObjectManager.get()->go_vector.size() - 1).get());

        w->mAPI = mAPI;

    	if (mAPI->textureManager.get()->addNewTexture("wall_vertical")) { mAPI->textureManager.get()->texture_map.at("wall_vertical").loadFromFile("Textures/wall_vertical.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_horizontal")) { mAPI->textureManager.get()->texture_map.at("wall_horizontal").loadFromFile("Textures/wall_horizontal.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_corner_bottom_left")) { mAPI->textureManager.get()->texture_map.at("wall_corner_bottom_left").loadFromFile("Textures/wall_corner_bottom_left.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_corner_bottom_right")) { mAPI->textureManager.get()->texture_map.at("wall_corner_bottom_right").loadFromFile("Textures/wall_corner_bottom_right.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_corner_top_left")) { mAPI->textureManager.get()->texture_map.at("wall_corner_top_left").loadFromFile("Textures/wall_corner_top_left.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_corner_top_right")) { mAPI->textureManager.get()->texture_map.at("wall_corner_top_right").loadFromFile("Textures/wall_corner_top_right.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_t_left")) { mAPI->textureManager.get()->texture_map.at("wall_t_left").loadFromFile("Textures/wall_t_left.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_t_right")) { mAPI->textureManager.get()->texture_map.at("wall_t_right").loadFromFile("Textures/wall_t_right.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_t_top")) { mAPI->textureManager.get()->texture_map.at("wall_t_top").loadFromFile("Textures/wall_t_top.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_t_bottom")) { mAPI->textureManager.get()->texture_map.at("wall_t_bottom").loadFromFile("Textures/wall_t_bottom.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_pillar")) { mAPI->textureManager.get()->texture_map.at("wall_pillar").loadFromFile("Textures/wall_pillar.png"); }
    	if (mAPI->textureManager.get()->addNewTexture("wall_cross")) { mAPI->textureManager.get()->texture_map.at("wall_cross").loadFromFile("Textures/wall_cross.png"); }

    	w->blockUpdate(NULL);
    }
}

void initializeMod(modAPI* mAPI)
{
    mAPI->control_override.set(controller);
    mAPI->worldFileEntryE.add_event(loadFromWorldLine);

    pl = new player(mAPI);
    mAPI->gameObjectManager.get()->go_vector.push_back(std::unique_ptr<gameObject>(pl));
}
