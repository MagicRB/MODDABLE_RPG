#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <vector>
#include "Tile.hpp"

class TileManager
{
	public:
		std::vector<Tile> tiles;

		TileManager();
		~TileManager();
	protected:

	private:

};

#endif // TILE_MANAGER_H