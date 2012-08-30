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
 *  \file   GlobalHighScoreRow.h
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DATASTORE_GLOBALHIGHSCOREROW_H_
#define FORESTRUNNER_DATASTORE_GLOBALHIGHSCOREROW_H_

#include "forestrunner/datastore/UserHighScoreRow.h"

namespace forestrunner {
namespace    datastore {




struct GlobalHighScoreRow:
    public UserHighScoreRow
{
    std::string username;
};




} // namespace datastore 
} // namespace forestrunner 

#endif // GLOBALHIGHSCOREROW_H_
