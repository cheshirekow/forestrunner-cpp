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
 *  \file   Dispatcher.h
 *
 *  \date   Sep 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_GAME_DISPATCHER_H_
#define FORESTRUNNER_GAME_DISPATCHER_H_

namespace forestrunner {
namespace         game {

/// base class for the state graph, provides interface accessible by iOS
class Dispatcher
{
    public:
        virtual ~Dispatcher(){}

        virtual void startInitCycle()    =0;
        virtual void startInitRun()      =0;
        virtual void startLightingCycle()=0;
        virtual void startCartoonCycle() =0;

        virtual bool isPaused() =0;
        virtual bool isCrashed()=0;

};

} // namespace game 
} // namespace forestrunner 

#endif // DISPATCHER_H_
