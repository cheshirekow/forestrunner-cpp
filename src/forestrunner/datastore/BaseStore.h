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
 *  \file   BaseStore.h
 *
 *  \date   Sep 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DATASTORE_BASESTORE_H_
#define FORESTRUNNER_DATASTORE_BASESTORE_H_

#include "forestrunner/datastore/DataStore.h"
#include <sigc++/sigc++.h>

namespace forestrunner {
namespace    datastore {

class BaseStore :
    public forestrunner::DataStore
{
    public:
        sigc::signal<void,Key_t,const datastore::MapEntry&> sig_valueChanged;

    public:
        BaseStore();
        virtual ~BaseStore();

        virtual void markChanged(Key_t key);
};

} // namespace datastore 
} // namespace forestrunner 

#endif // BASESTORE_H_
