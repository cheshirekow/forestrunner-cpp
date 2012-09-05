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
 *  along with forestrunner.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   keys.h
 *
 *  \date   Sep 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_KEYS_H_
#define FORESTRUNNER_KEYS_H_

#include <string>

namespace forestrunner {
namespace         keys {

enum Key
{
    USERNAME = 0,
    HASH,

    PREF_SPEED,
    PREF_DENSITY,
    PREF_RADIUS,

    STAT_VERSION,
    STAT_LASTUSERROWID,
    STAT_LASTGLOBALROWID,

    ADV_PARTICIPATE,
    ADV_POSTPROCESS,
    ADV_CARTOON,
    ADV_LIGHTING,
    ADV_PATCHGRIDS,
    ADV_MAINGRID,
    ADV_GRADIENTFLOOR,
    ADV_LOGGING,
    ADV_WORLDROTATE,

    INVALID
};

}

typedef keys::Key Key_t;

const char* keystr( Key_t );
Key_t       strkey( const std::string& );

}















#endif // KEYS_H_
