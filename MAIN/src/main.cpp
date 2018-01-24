#include "main.h"

#include <iostream>
#include <map>

#include <cmath>

#include "player.hpp"
#include "door.hpp"

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
    }
}

void initializeMod(modAPI* mAPI)
{
    mAPI->control_override.set(controller);
    mAPI->worldFileEntryE.add_event(loadFromWorldLine);

    pl = new player(mAPI);
    mAPI->gameObjectManager.get()->go_vector.push_back(std::unique_ptr<gameObject>(pl));
}
