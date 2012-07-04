
/*
 *  @file   State.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for State class
 */


#include "State.h"

namespace   stategraph {


Ogre::Viewport*  State::s_viewport = 0;

void State::activate(Manager& mgr)
{
    m_connections[&mgr] =
        mgr.sig_update.connect(
                sigc::mem_fun(*this,&This_t::update) );
}

void State::deactivate(Manager& mgr)
{
    m_connections[&mgr].disconnect();
}

sigc::slot<void,Manager&> State::slot_activate()
{
    return sigc::mem_fun(*this,&This_t::activate);
}




} //namespace stategraph



