/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of forestrunner.
 *
 *  forestrunner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  forestrunner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   keys.cpp
 *
 *  \date   Sep 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/keys.h"
#include <map>

namespace forestrunner {

static const char* g_keyStore[] = {
    "username",
    "hash",
    "pref:velocity",
    "pref:density",
    "pref:radius",
    "stat:version",
    "stat:lastUserRowId",
    "stat:lastGlobalRowId",
    "adv:participate",
    "adv:postProcess",
    "adv:cartoon",
    "adv:lighting",
    "adv:patchGrids",
    "adv:mainGrid",
    "adv:gradientFloor",
    "adv:logging",
    "adv:worldRotate",
    0
};

static std::map<std::string,Key_t> g_revKeyStore;

const char* keystr( Key_t key )
{
    return g_keyStore[key];
}

Key_t strkey( const std::string& str )
{
    if(g_revKeyStore.size() < 1 )
    {
        const char** pString = g_keyStore;
        for( int i=0; *pString != 0; i++)
        {
            g_revKeyStore[*pString] = (Key_t)i;
            pString++;
        }
    }

    if(g_revKeyStore.find(str) == g_revKeyStore.end())
        return keys::INVALID;

    return g_revKeyStore[str];
}


}







