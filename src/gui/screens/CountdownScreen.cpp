/*
 *  \file   CountdownScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "CountdownScreen.h"

#include <cassert>
#include "game/Game.h"

CountdownScreen::CountdownScreen(int which):
    m_which(which)
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();

    switch(which)
    {
        case 3:
            m_root = wmgr.loadLayoutFromFile("countdown3.layout");
            m_next = "countdown2";
            break;

        case 2:
            m_root = wmgr.loadLayoutFromFile("countdown2.layout");
            m_next = "countdown1";
            break;

        case 1:
            m_root = wmgr.loadLayoutFromFile("countdown1.layout");
            m_next = "running";
            break;

        default:
            assert(false);
            break;
    }

    m_anim_enter = "PulseIn";
    m_anim_exit  = "PulseOut";
}

CountdownScreen::~CountdownScreen()
{

}

void CountdownScreen::exec()
{
    if(m_which==3)
        m_dispatcher->initRun();
    m_sig_transition.emit(m_next);
}
