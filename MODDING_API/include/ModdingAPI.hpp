#ifndef MODDING_API_H
#define MODDING_API_H

#include <functional>
#include <string>
#include <vector>

#include "TextureManager.hpp"
#include "goManager.hpp"

template <class func>
struct event_handle {
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

struct mod_info {
public:
    const char* internal_name;
    const char* display_name;
    int version_major;
    int version_minor;
};

class modAPI
{
    public:
        TextureManager*                             grtTexm();
        void                                        sroTexm(TextureManager* rtexm);
        goManager*                                  grtGom();
        void                                        sroGom(goManager* rtexm);
        sf::RenderWindow*                           grtWindow();
        void                                        sroWindow(sf::RenderWindow* window);
        sf::View*                                   grtView();
        void                                        sroView(sf::View* view);

        sf::Event*                                  grtEvent();
        void                                        sroEvent(sf::Event* event);

        void                                        sorControl(std::function<void(modAPI*, sf::Event)> mcorapix);
        std::function<void(modAPI*, sf::Event)>     gorControl();

        event_handle<std::function<void(modAPI*, std::string)>> worldFileEntryE;
        event_handle<std::function<void(modAPI*)>> inputE;

        int windowScale = 2;

        std::map<unsigned short int, std::function<void(modAPI*)>> keyBindMap;

        modAPI();
        ~modAPI();
    protected:

    private:

        TextureManager*         ptexm;
        goManager*              pgom;
        sf::RenderWindow*       pwindow;
        sf::View*               pview;
        sf::Event*              pevent;

        std::function<void(modAPI*, sf::Event)> overrideControl;

};



#endif // MODDING_API_H
