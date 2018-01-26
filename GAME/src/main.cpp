#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "WorldLoader.hpp"
#include "goManager.hpp"
#include "modManager.hpp"
#include "ModdingAPI.hpp"

int main()
{
	modManager		mm;
	TextureManager  texm;
	goManager		gom;
	modAPI			mapi;
	WorldLoader		wl;
	sf::View        view(sf::Vector2f(0, 0), sf::Vector2f(10*32, 10*32/4*3));
	sf::Event		event;

	std::cout << "Welcome to SFML_RPG version 0.0000001" << std::endl;
	std::cout << "-------------------------------------" << std::endl;

	sf::RenderWindow Window(sf::VideoMode(10*32*mapi.windowScale, 10*32/4*3*mapi.windowScale), "My Window");

	mapi.gameObjectManager.set(&gom);
	mapi.textureManager.set(&texm);
	mapi.window.set(&Window);
	mapi.view.set(&view);
	mapi.event.set(&event);

	Window.setView(view);
	Window.setVerticalSyncEnabled(true);
	Window.setFramerateLimit(60);

	mm.loadMod("libMAIN", "Mods/", &mapi);

	wl.loadWorld("map.txt", &texm, &gom, &mm, &mapi);

	while (Window.isOpen()) {
		Window.pollEvent(event);

		if (mapi.control_override.get() == NULL) {
			if (event.type == sf::Event::Closed) {
				Window.close();
			} else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
				Window.close();
			}
		} else {
			mapi.control_override.get()(&mapi, event);
		}

		if (Window.isOpen())
        {
            Window.clear();
            if(gom.go_vector.size() != 0) {
                for (unsigned int i = 0; i < gom.go_vector.size(); i++) {
                    gom.go_vector.at(i)->render(&Window);
                }
            }
            chunkified_pos<int> ch = world_to_chunk(mapi.view.get()->getCenter().x / 32, mapi.view.get()->getCenter().y / 32);
            for (int x = ch.chunk_x - 1; x <= ch.chunk_x + 1; x++) {
                for (int y = ch.chunk_y - 1; y <= ch.chunk_y + 1; y++) {
                    for (int px = 0; px < 64; px++) {
                        for (int py = 0; py < 64; py++) {
                            if (mapi.chunks.count(std::pair<int, int>(x, y)) != 0 && mapi.chunks[std::pair<int, int>(x, y)].objects[px][py] != NULL) {
                                mapi.chunks.at(std::pair<int, int>(x, y)).objects[px][py]->render(mapi.window.get());
                            }
                        }
                    }
                }
            }

            Window.display();
        }
	}

    Window.close();

	mm.closeAllMods();

	return 0;
}
