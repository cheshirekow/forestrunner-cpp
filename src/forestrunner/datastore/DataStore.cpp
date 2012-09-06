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

#include "forestrunner/datastore/DataStore.h"
#include "forestrunner/desktop/DataStore.h"



namespace forestrunner {


size_t DataStore::sm_numRows = 10;



DataStore::DataStore()
{
    using namespace datastore;
    using namespace keys;

    m_map[USERNAME] = new MapEntryT<std::string>("Anon");
    m_map[HASH]     = new MapEntryT<std::string>("0");

    m_map[PREF_DENSITY]  = new MapEntryT<int>(0);
    m_map[PREF_RADIUS]   = new MapEntryT<int>(0);
    m_map[PREF_SPEED]    = new MapEntryT<int>(0);

    m_map[STAT_VERSION]           = new MapEntryT<int>(5);
    m_map[STAT_LASTUSERROWID]     = new MapEntryT<int>(0);
    m_map[STAT_LASTGLOBALROWID]   = new MapEntryT<int>(0);

    m_map[ADV_PARTICIPATE]    = new MapEntryT<bool>(true);
    m_map[ADV_POSTPROCESS]    = new MapEntryT<bool>(false);
    m_map[ADV_CARTOON]        = new MapEntryT<bool>(true);
    m_map[ADV_LIGHTING]       = new MapEntryT<bool>(false);
    m_map[ADV_PATCHGRIDS]     = new MapEntryT<bool>(false);
    m_map[ADV_MAINGRID]       = new MapEntryT<bool>(true);
    m_map[ADV_GRADIENTFLOOR]  = new MapEntryT<bool>(false);
    m_map[ADV_LOGGING]        = new MapEntryT<bool>(false);
    m_map[ADV_WORLDROTATE]    = new MapEntryT<bool>(true);

    m_userScores.reserve(sm_numRows);
    m_globalScores.reserve(sm_numRows);
}




DataStore::~DataStore()
{
    using namespace datastore;

    for( Map_t::iterator iPair = m_map.begin(); iPair != m_map.end(); iPair++ )
        delete iPair->second;

    m_map.clear();
}



const DataStore::UserVec_t& DataStore::userScores()
{
    return m_userScores;
}

const DataStore::GlobalVec_t& DataStore::globalScores()
{
    return m_globalScores;
}

DataStore* DataStore::create( datastore::Backend_t backend)
{
    using namespace datastore::backend;
    switch(backend)
    {
        case SOCI:
            return new desktop::DataStore();
    }
    
    return 0;
}


} // namespace forestrunner 
