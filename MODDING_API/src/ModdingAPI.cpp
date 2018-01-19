#include "ModdingAPI.hpp"

TextureManager* modAPI::grtTexm()
{
    return ptexm;
}

void modAPI::sroTexm(TextureManager* rtexm)
{
    ptexm = rtexm;
}

goManager* modAPI::grtGom()
{
    return pgom;
}

void modAPI::sroGom(goManager* rgom)
{
    pgom = rgom;
}

sf::RenderWindow* modAPI::grtWindow()
{
    return pwindow;
}
void modAPI::sroWindow(sf::RenderWindow* window)
{
    pwindow = window;
}

sf::View* modAPI::grtView()
{
    return pview;
}
void modAPI::sroView(sf::View* view)
{
    pview = view;
}

sf::Event* modAPI::grtEvent()
{
    return pevent;
}

void modAPI::sroEvent(sf::Event* event)
{
    pevent = event;
}

void modAPI::sorControl(std::function<void(modAPI*, sf::Event)> cor)
{
    overrideControl = cor;
}

std::function<void(modAPI*, sf::Event)>  modAPI::gorControl()
{
    return overrideControl;
}

modAPI::modAPI()
{

}

modAPI::~modAPI()
{

}
