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
 *  \file   DataStore.cpp
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/desktop/DataStore.h"

#include <cstdlib>

#ifdef FORESTRUNNER_OSX
#include <pwd.h>
#include <unistd.h>
#endif

namespace forestrunner {
namespace      desktop {



DataStore::DataStore()
{


#ifdef FORESTRUNNER_LINUX
    m_dataDir = getenv("HOME");
#elif FORESTRUNNER_WINDOWS
    m_dataDir = getenv("APPDATA");
#elif FORESTRUNNER_OSX
    const struct passwd* pwd = getpwuid(getuid());
    m_dataDir = pwd->pw_dir;
#endif

}







} // namespace desktop 
} // namespace forestrunner 
