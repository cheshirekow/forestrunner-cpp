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
 *  \file   StateGraph.h
 *
 *  \date   Sep 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_GAME_STATEGRAPH_H_
#define FORESTRUNNER_GAME_STATEGRAPH_H_

#include <sigc++/sigc++.h>
#include <OgreMath.h>

namespace forestrunner {
namespace         game {

class InitCycle
{
    public:
        enum Step
        {
            CLEAR_PATCHES   = 0,
            FREE_MESHES,
            CREATE_MESHES,
            INIT_PATCHES,
            DONE,
            NUM_STEPS
        };

    private:
        int m_step;
        int m_nPatches;
        int m_iPatch;

    public:
        sigc::signal<void,int>      sig_clearPatch;
        sigc::signal<void>          sig_freeMeshes;
        sigc::signal<void>          sig_createMeshes;
        sigc::signal<void,int>      sig_initPatch;
        sigc::signal<void,float>    sig_progress;

    public:
        InitCycle();
        ~InitCycle();
        void setNumPatches(int nPatches);
        void reset();
        bool step();




};

/// dispatcher for update() events which passes the event to the appropriate
/// method of the game
class StateGraph
{
    public:
        enum State
        {
            INIT_CYCLE,
            INIT_RUN,
            SHOULD_RUN,
            RUNNING,
            PAUSED,
            CRASHED,
        };

    private:
        State               m_state;

    public:
        sigc::signal<void>              sig_initRun;
        sigc::signal<void>              sig_flushTimer;
        sigc::signal<void,Ogre::Real>   sig_stepRun;

        InitCycle   initCycle;

        StateGraph();
        ~StateGraph();

        /// performs one step of the current action, returns true if more
        /// work needs to be done
        bool step(Ogre::Real tpf);

        /// called from the UI when the user pauses the game, changes state
        /// to paused
        void pause();

        /// called from the UI thread when the user resumes from paused
        /// without changing the data store
        void resumeFromPaused();

        /// called from the UI thread when the user starts a new game after
        /// crashing or after initialization
        void startNewRun();

        /// called from the game when the user crashes
        void crash();

        /// return the current state (useful when step returns false and we
        /// want to know if the game crashed or was paused)
        State getState();

};


} // namespace game 
} // namespace forestrunner 

#endif // STATEGRAPH_H_
