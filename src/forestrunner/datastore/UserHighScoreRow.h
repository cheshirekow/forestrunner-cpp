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
 *  \file   UserHighScoreRow.h
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DATASTORE_USERHIGHSCOREROW_H_
#define FORESTRUNNER_DATASTORE_USERHIGHSCOREROW_H_

#include <string>

namespace forestrunner {
namespace    datastore {


struct UserHighScoreRow
{
    bool         isCurrent;
    long         id;
    long         date;
    double       score;

    /// initialize with isCurrent = false
    UserHighScoreRow();

    /// enforces strict ordering, lexographical score,date (earlier is
    /// better)
    /**
     *  @note if `a == b` (as in their score, date, and id are all equal),
     *        then `a.lessThan(b) == b.lessThan(a) == false`
     */
    bool lessThan(const UserHighScoreRow& other) const;
};


} // namespace datastore 
} // namespace forestrunner 


bool operator<( const forestrunner::datastore::UserHighScoreRow& a,
                const forestrunner::datastore::UserHighScoreRow& b );


bool operator>( const forestrunner::datastore::UserHighScoreRow& a,
                const forestrunner::datastore::UserHighScoreRow& b );




#endif // USERHIGHSCOREROW_H_
