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
 *  \file   datastore.cpp
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */



#include "forestrunner/datastore/Map.h"

namespace forestrunner {
namespace    datastore {

// specializations
template <> EntryType asType<float>         (){ return FLOAT; }
template <> EntryType asType<double>        (){ return DOUBLE; }
template <> EntryType asType<int>           () { return INT; }
template <> EntryType asType<std::string>   (){ return STRING; }

} // namespace data store
} // namespace forestrunner









