#include "modManager.hpp"

#include <iostream>

void modManager::loadMod(std::string mod_name, std::string path, modAPI* mapi)
{
    void (*init_mod)(modAPI*) = NULL;

#if WIN32
    mods[mod_name] = dlopen((path + mod_name + ".dll").c_str(), RTLD_LAZY);
#elif UNIX
    mods[mod_name] = dlopen((path + mod_name + ".so").c_str(), RTLD_LAZY);
#endif
    char* error = dlerror();
    if (error != 0)
    {
        std::cout << error << std::endl;
        return;
    }

    init_mod = (void (*)(modAPI*))dlsym(mods.at(mod_name), "initializeMod");

    error = dlerror();
    if (error != 0)
    {
        std::cout << "Invalid mod file" << std::endl;
        return;
    }

    init_mod(mapi);
}

void modManager::closeAllMods()
{
    std::map<std::string, void*>::iterator it = mods.begin();
    while(it != mods.end())
    {
        dlclose(it->second);
    }
    
    mods.erase(mods.begin(), mods.end());
}
