#ifndef MODDING_API_H
#define MODDING_API_H

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include "TextureManager.hpp"
#include "goManager.hpp"

template <class func>
struct event_handler {
public:
    void add_event(func f)
    {
        event_vector.push_back(f);
    }
    std::vector<func> get_event_vector()
    {
        return event_vector;
    }
private:
    std::vector<func> event_vector;
};

template <class ref>
struct reference_holder {
public:
    void set(ref reference)
    {
        storage = reference;
    }
    ref get()
    {
        return storage;
    }
private:
    ref storage;
};

struct mod_info {
public:
    const char* internal_name;
    const char* display_name;
    int version_major;
    int version_minor;
};

struct chunk {
public:
    std::array<std::array<gameObject*, 64>, 64> objects;
};

template <class T>
struct chunkified_pos {
public:
    int chunk_x;
    int chunk_y;
    int x;
    int y;
};

chunkified_pos<int> world_to_chunk(int px, int py);

class modAPI
{
    public:
        reference_holder<TextureManager*> textureManager;
        reference_holder<sf::RenderWindow*> window;
        reference_holder<goManager*> gameObjectManager;
        reference_holder<sf::View*> view;
        reference_holder<sf::Event*> event;
        reference_holder<std::function<void(modAPI*, sf::Event)>> control_override;

        event_handler<std::function<void(modAPI*, std::string)>> worldFileEntryE;
        event_handler<std::function<void(modAPI*)>> inputE;

        int windowScale = 2;

        std::map<unsigned short int, std::function<void(modAPI*)>> keyBindMap;

        std::map<std::pair<int, int>, chunk> chunks;

        modAPI();
        ~modAPI();
    protected:

    private:

};



#endif // MODDING_API_H
