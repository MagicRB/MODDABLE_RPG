#include "ModdingAPI.hpp"

#include <cmath>
#include <iostream>

chunkified_pos<int> world_to_chunk(int px, int py)
{
    chunkified_pos<int> ch;
    ch.chunk_x = floor(px / 64.0f);
    ch.chunk_y = floor(py / 64.0f);
    ch.x = abs(px) % 64;
    ch.y = abs(py) % 64;

    if (ch.chunk_x < 0) { ch.x = 64 - ch.x; }
    if (ch.chunk_y < 0) { ch.y = 64 - ch.y; }

    return ch;
}

modAPI::modAPI()
{

}

modAPI::~modAPI()
{

}
