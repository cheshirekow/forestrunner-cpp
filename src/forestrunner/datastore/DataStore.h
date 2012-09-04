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
 *  \file   DataStore.h
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DATASTORE_DATASTORE_H_
#define FORESTRUNNER_DATASTORE_DATASTORE_H_

#include "forestrunner/datastore/Map.h"
#include "forestrunner/datastore/UserHighScoreRow.h"
#include "forestrunner/datastore/GlobalHighScoreRow.h"

namespace forestrunner{



/// base class and interface for data storage (preferences, user scores)
/**
 *  Also implements a generic property map
 */
class DataStore
{
    protected:
        datastore::Map_t  m_map;    ///< map of all the stuff we need

    public:
        /// initializes the map with some default data
        DataStore();

        /// destroys all the map entries
        virtual ~DataStore();

        /// return the value of the requested key
        template <typename T>
        T& get( const std::string& key )
        {
            assert( m_map.find(key) != m_map.end() );
            assert( m_map[key]->type() == datastore::asType<T>() );
            return m_map[key]->get<T>();
        }

        /// return the value of the requested key
        template <typename T>
        const T& get( const std::string& key ) const
        {
            assert( m_map.find(key) != m_map.end() );
            const datastore::MapEntry* entry= m_map[key];

            assert( entry->type() == datastore::asType<T>() );
            return entry->get<T>();
        }

        /// read data from the backend (database) and fill the map with
        /// entries that are found, also create datbase if it doesn't exist
        virtual void init(){}

        /// write settings data to the backend (database)
        virtual void flush(){}

        /// write the users score to the database, using current preferences
        /// for the rest of the info
        virtual void write_score(double score){}

        /// read out the sorted scores after writing
        virtual void sync_scores(){}

        /// close database connections, etc
        virtual void fini(){}

        /// extracts a value into the specified variable and returns true if
        /// the value has changed
        template <typename T>
        bool extract( T& out, const std::string& key)
        {
            bool result = ( out != get<T>(key) );
            if(result)
                out = get<T>(key);
            return result;
        }






};

} // namespace forestrunner 

#endif // DATASTORE_H_
