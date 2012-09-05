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
 *  \file   datastore.h
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DATASTORE_H_
#define FORESTRUNNER_DATASTORE_H_

#include "forestrunner/keys.h"

#include <cassert>
#include <ostream>
#include <map>
#include <string>



namespace forestrunner {
namespace    datastore {
    enum EntryType
    {
        BOOL,
        INT,
        STRING,
        INVALID
    };

    /// returns a numeric const (actually enum) unique to the
    /// type of data store in the union
    template <typename T>
    EntryType asType(){ return INVALID; }

    // forward declaration
    template <typename T> struct MapEntryT;

    /// base class (interface) for a map entry, basically a union with
    /// type info stored, also type can't be changed
    struct MapEntry
    {
        /// needs a vtable
        virtual ~MapEntry(){}

        /// return the type of the entry
        virtual EntryType   type() const=0;

        /// return the value stored in this entry
        /**
         *  @note be sure to check `type() == asType<T>()` before casting
         */
        template <typename T>
        T& get()
        {
            assert( type() == asType<T>() );
            return static_cast< MapEntryT<T>* >(this)->value;
        }

        /// return the value stored in this entry
        /**
         *  @note be sure to check `type() == asType<T>()` before casting
         */
        template <typename T>
        const T& get() const
        {
            assert( type() == asType<T>() );
            return static_cast< const MapEntryT<T>* >(this)->value;
        }

        virtual std::ostream& write(std::ostream& stream) const=0;
    };

    /// leaf class for map entry (basically a template union)
    template <typename T>
    struct MapEntryT:
        public MapEntry
    {
        T           value;    ///< value stored

        /// default constructor
        MapEntryT(){}

        /// construct with argument
        MapEntryT(const T& arg ):value(arg){}

        /// needs a vtable
        virtual ~MapEntryT(){}

        /// return EntryType indicating the kind of value that is stored
        EntryType   type() const { return asType<T>(); }

        virtual std::ostream& write(std::ostream& stream) const
        {
            return stream << value;
        }
    };


    typedef std::map<Key_t, MapEntry* > Map_t;

} // namespace data store
} // namespace forestrunner


std::ostream& operator<<(
        std::ostream& stream,
        const forestrunner::datastore::MapEntry& entry );











#endif // DATASTORE_H_
