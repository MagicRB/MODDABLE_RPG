#include "WorldLoader.hpp"

#include <fstream>
#include <iostream>

void WorldLoader::loadWorld (std::string world, TextureManager* texm, goManager* gom, modManager* mm, modAPI* mapi)
{
	std::string line;

	std::ifstream file(world_folder + world);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line != "")
			{
				for (unsigned short int i = 0; i < mapi->worldFileEntryE.get_event_vector().size(); i++)
				{
					mapi->worldFileEntryE.get_event_vector().at(i)(mapi, line);
				}
			}
		}
		file.close();
	}
}

WorldLoader::WorldLoader()
{

}

WorldLoader::~WorldLoader()
{

}
