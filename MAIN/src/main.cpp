#include "main.h"

#include <iostream>
#include <map>

#include <cmath>

#include "player.hpp"
#include "Tile.hpp"
#include "door.hpp"

std::map<std::string, Tile> tile_defs;
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
        int mouseX = sf::Mouse::getPosition(*mAPI->grtWindow()).x;
        int mouseY = sf::Mouse::getPosition(*mAPI->grtWindow()).y;
        sf::Vector2i mouse(mouseX, mouseY);
        if (sqrt( pow(mAPI->grtWindow()->mapPixelToCoords(mouse).x - pl->getPosition().x, 2) + pow( mAPI->grtWindow()->mapPixelToCoords(mouse).y - pl->getPosition().y, 2) ) <= 60) {
            for (int i = 0; i < mAPI->grtGom()->go_vector.size(); i++) {
                if (mAPI->grtGom()->go_vector.at(i)->getBounds().contains(mAPI->grtWindow()->mapPixelToCoords(mouse))) {
                    mAPI->grtGom()->go_vector.at(i)->interact(pl);
                }
            }
        }
    }

    if (event.type == sf::Event::Closed) {
		mAPI->grtWindow()->close();
	} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
		mAPI->grtWindow()->close();
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

    if (operation == ":TILE") {
    	tile_defs[tokens.at(0)] = Tile();
    	mAPI->grtTexm()->addNewTexture(tokens.at(1));
    	mAPI->grtTexm()->texture_map.at(tokens.at(1)).loadFromFile("Textures/" + tokens.at(1) + ".png");
    	tile_defs.at(tokens.at(0)).setTexture(mAPI->grtTexm()->texture_map.at(tokens.at(1)));
        if (tokens.at(2) == "True" || tokens.at(2) == "true")
            tile_defs.at(tokens.at(0)).collidable = true;
        else
            tile_defs.at(tokens.at(0)).collidable = false;
    } else if (operation == ":CREATE") {
    	mAPI->grtGom()->go_vector.push_back(std::unique_ptr<gameObject>(new Tile(tile_defs.at(tokens.at(0)))));
    	Tile* t = dynamic_cast<Tile*>(mAPI->grtGom()->go_vector.at(mAPI->grtGom()->go_vector.size() - 1).get());
    	t->setTilePosition(atoi(tokens.at(1).c_str()), atoi(tokens.at(2).c_str()));
    } else if (operation == ":DOOR") {
    	mAPI->grtGom()->go_vector.push_back(std::unique_ptr<gameObject>(new door()));
    	door* d = dynamic_cast<door*>(mAPI->grtGom()->go_vector.at(mAPI->grtGom()->go_vector.size() - 1).get());
    	d->setTilePosition(atoi(tokens.at(0).c_str()), atoi(tokens.at(1).c_str()));
        mAPI->grtTexm()->addNewTexture("door");
    	mAPI->grtTexm()->texture_map.at("door").loadFromFile("Textures/door.png");
    	d->setTexture(mAPI->grtTexm()->texture_map.at("door"));
    }
}

void initializeMod(modAPI* mAPI)
{
    mAPI->sorControl(controller);
    mAPI->worldFileEntryE.add_event(loadFromWorldLine);

    pl = new player(mAPI);
    mAPI->grtGom()->go_vector.push_back(std::unique_ptr<gameObject>(pl));
}