#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

class TextureManager
{
	public:
		std::map<std::string, sf::Texture> texture_map;

		bool addNewTexture(std::string);

		TextureManager();
		~TextureManager();
	protected:
		
	private:
		
};

#endif //TEXTURE_MANAGER_H