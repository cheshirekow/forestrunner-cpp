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
 *  \file   StateGraph.cpp
 *
 *  \date   Sep 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/game/StateGraph.h"

namespace forestrunner {
namespace         game {


InitCycle::InitCycle()
{
    m_step      = DONE;
    m_iPatch    = 0;
    m_nPatches  = 1;
}

InitCycle::~InitCycle()
{

}

void InitCycle::setNumPatches(int nPatches)
{
    m_nPatches = nPatches;
}

void InitCycle::reset()
{
    m_step   = CLEAR_PATCHES;
    m_iPatch = 0;
}

bool InitCycle::step()
{
    switch(m_step)
    {
        case CLEAR_PATCHES:
        {
            sig_clearPatch.emit(m_iPatch++);
            if(m_iPatch >= m_nPatches)
            {
                m_step++;
                m_iPatch = 0;
            }
            break;
        }

        case FREE_MESHES:
            sig_freeMeshes.emit();
            m_step++;
            break;

        case CREATE_MESHES:
            sig_createMeshes.emit();
            m_step++;
            break;

        case INIT_PATCHES:
        {
            sig_initPatch.emit(m_iPatch++);
            if(m_iPatch >= m_nPatches)
            {
                m_step++;
                m_iPatch = 0;
            }
            break;
        }

        case DONE:
        {
            m_step++;
            sig_finished.emit();
            return false;
        }

        default:
            return false;
    }

    sig_progress.emit( ( m_step + (m_iPatch / (float)m_nPatches) )
                        / (float)(NUM_STEPS-1) );

    return true;
}










CartoonCycle::CartoonCycle()
{
    m_iPatch    = 0;
    m_nPatches  = 1;
}

CartoonCycle::~CartoonCycle()
{

}

void CartoonCycle::setNumPatches(int nPatches)
{
    m_nPatches = nPatches;
}

void CartoonCycle::reset()
{
    m_iPatch = 0;
}

bool CartoonCycle::step()
{
    if(m_iPatch >= m_nPatches)
        return false;

    sig_clearPatch.emit(m_iPatch);
    sig_initPatch.emit(m_iPatch);
    m_iPatch++;
    return true;
}









StateGraph::StateGraph()
{
    m_state = INVALID;
}

StateGraph::~StateGraph()
{

}

bool StateGraph::step(Ogre::Real tpf)
{
    switch(m_state)
    {
        case INIT_CYCLE:
        {
            if(!initCycle.step())
                m_state = FINISH;
            return true;
        }

        case INIT_RUN:
        {
            sig_initRun.emit();
            m_state = FINISH;
            return true;
        }

        case SHOULD_RUN:
            sig_flushTimer.emit();
            m_state = RUNNING;
            return true;

        case RUNNING:
            sig_stepRun.emit(tpf);
            return true;

        case PAUSED:
            return false;

        case CRASHED:
            return false;

        case LIGHTING_START:
        {
            sig_setLighting.emit();
            m_state = FINISH;
            return true;
        }

        case CARTOON_CYCLE:
        {
            if(!cartoonCycle.step())
                m_state = FINISH;
            return true;
        }

        case FINISH:
        {
            // note, we have to set idle before emmitting the signal because
            // in some cases the signal handler will change the state to
            // something else
            m_state = IDLE;
            sig_cycleFinished.emit();
            return true;
        }

        default:
            return false;
    }
}

void StateGraph::pause()
{
    m_state = PAUSED;
    sig_paused.emit();
}

void StateGraph::crash()
{
    m_state = CRASHED;
    sig_crashed.emit();
}

void StateGraph::startInitRun()
{
    m_state = INIT_RUN;
}


void StateGraph::play()
{
    m_state = SHOULD_RUN;
}

void StateGraph::startInitCycle()
{
    m_state = INIT_CYCLE;
    initCycle.reset();
}

void StateGraph::startLightingCycle()
{
    m_state = LIGHTING_START;
}

void StateGraph::startCartoonCycle()
{
    m_state = CARTOON_CYCLE;
    cartoonCycle.reset();
}


StateGraph::State StateGraph::getState()
{
    return m_state;
}


bool StateGraph::isPaused()
{
    return m_state == PAUSED;
}

bool StateGraph::isCrashed()
{
    return m_state == CRASHED;
}


} // namespace game 
} // namespace forestrunner 
