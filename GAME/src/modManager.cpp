#include "modManager.hpp"

#include <iostream>
#include <ModdingAPI.hpp>

void modManager::loadMod(std::string mod_name, std::string path, modAPI* mapi)
{
    void (*init_mod)(modAPI*) = NULL;

    void* mod;

#if WIN32
    mod = dlopen((path + mod_name + ".dll").c_str(), RTLD_LAZY);
#elif __linux__
    mod = dlopen((path + mod_name + ".so").c_str(), RTLD_LAZY);
#endif
    char* error = dlerror();
    if (error != 0)
    {
        std::cout << error << std::endl;
        return;
    }

    init_mod = (void (*)(modAPI*))dlsym(mod, "initializeMod");
    mod_info* minfo = (mod_info*)dlsym(mod, "minfo");
    std::cout << "Loading mod with display name: " << minfo->display_name << "\nInternal name: " << minfo->internal_name << "\nVersion: " << minfo->version_major << "." << minfo->version_minor << std::endl;

    mods[minfo->internal_name] = mod;

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
    std::map<std::string, void*>::iterator it;

    for ( it = mods.begin(); it != mods.end(); ++it )
    {
        //dlclose(it->second);
    }

    //dlclose(mods.at("MAIN"));

    mods.erase(mods.begin(), mods.end());
}
