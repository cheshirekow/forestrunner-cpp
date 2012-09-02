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



namespace forestrunner {




DataStore::DataStore()
{
    using namespace datastore;

    m_map["username"] = new MapEntryT<std::string>("Anon");
    m_map["hash"]     = new MapEntryT<std::string>("0");

    m_map["pref:density"]  = new MapEntryT<int>(0);
    m_map["pref:radius"]   = new MapEntryT<int>(0);
    m_map["pref:velocity"] = new MapEntryT<int>(0);

    m_map["stat:version"]           = new MapEntryT<int>(5);
    m_map["stat:lastUserRowId"]     = new MapEntryT<int>(0);
    m_map["stat:lastGlobalRowId"]   = new MapEntryT<int>(0);

    m_map["adv:participate"]    = new MapEntryT<bool>(true);
    m_map["adv:postProcess"]    = new MapEntryT<bool>(false);
    m_map["adv:fogFilter"]      = new MapEntryT<bool>(false);
    m_map["adv:cartoon"]        = new MapEntryT<bool>(true);
    m_map["adv:lighting"]       = new MapEntryT<bool>(false);
    m_map["adv:patchGrids"]     = new MapEntryT<bool>(false);
    m_map["adv:mainGrid"]       = new MapEntryT<bool>(true);
    m_map["adv:gradientFloor"]  = new MapEntryT<bool>(false);
    m_map["adv:logging"]        = new MapEntryT<bool>(false);
    m_map["adv:worldRotate"]    = new MapEntryT<bool>(true);
}




DataStore::~DataStore()
{
    using namespace datastore;

    for( Map_t::iterator iPair = m_map.begin(); iPair != m_map.end(); iPair++ )
        delete iPair->second;

    m_map.clear();
}




} // namespace forestrunner 
