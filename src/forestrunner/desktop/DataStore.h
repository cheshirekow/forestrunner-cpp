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

#ifndef FORESTRUNNER_DESKTOP_DATASTORE_H_
#define FORESTRUNNER_DESKTOP_DATASTORE_H_

#include "forestrunner/datastore/DataStore.h"

namespace forestrunner {
namespace      desktop {


class DataStore:
    public forestrunner::DataStore
{
    public:
        typedef forestrunner::DataStore Base_t;

    private:
        std::string     m_dataDir;

    public:
        /// simply assigns the value of m_dataDir
        DataStore();

        /// need to be virtual, does nothing
        virtual ~DataStore(){}

        /// if necessary, create, then connect to database and then read in
        /// any entries from the opened database
        virtual void init();

        /// iterate over the map and write entries into the database
        virtual void flush();

        /// record a new score for the user, adding it to the database
        virtual void write_score(double score);

        /// read out updated list of best scores from database
        virtual void sync_scores();

        /// close connection to database
        virtual void fini();
};


} // namespace desktop 
} // namespace forestrunner 

#endif // DATASTORE_H_
