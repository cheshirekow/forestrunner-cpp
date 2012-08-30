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
 *  \file   UserHighScoreRow.cpp
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/datastore/UserHighScoreRow.h"

namespace forestrunner {
namespace    datastore {




UserHighScoreRow::UserHighScoreRow()
{
    isCurrent = false;
}




bool UserHighScoreRow::lessThan(const UserHighScoreRow& other) const
{
    if( score < other.score )
        return true;
    if( score > other.score)
        return false;
    if( date < other.date )
        return true;
    if( date > other.date )
        return false;
    if( id < other.id )
        return true;
    return false;
}




} // namespace datastore 
} // namespace forestrunner 






bool operator<( const forestrunner::datastore::UserHighScoreRow& a,
                const forestrunner::datastore::UserHighScoreRow& b )
{
    return a.lessThan(b);
}

bool operator>( const forestrunner::datastore::UserHighScoreRow& a,
                const forestrunner::datastore::UserHighScoreRow& b )
{
    return b.lessThan(a);
}
