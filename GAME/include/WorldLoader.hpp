#ifndef WORLD_LOADER_H
#define WORLD_LOADER_H

#include <string>

#include "TextureManager.hpp"
#include "goManager.hpp"
#include "ModdingAPI.hpp"
#include "modManager.hpp"

class WorldLoader
{
    public:
        void loadWorld(std::string world, TextureManager* texm, goManager* tm, modManager* mm, modAPI* mapi);

        std::string world_folder = "worlds/";

        WorldLoader();
        ~WorldLoader();
	protected:

	private:
};

#endif //WORLD_LOADER_H