#ifndef __MAIN_H__
#define __MAIN_H__

#include "ModdingAPI.hpp"

extern "C"
{

    extern void initializeMod(modAPI* mapi);

    mod_info minfo = {"MAIN", "MAIN", 1, 0};

}

#endif // __MAIN_H__
