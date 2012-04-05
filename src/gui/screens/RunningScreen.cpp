/*
 *  \file   RunningScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/RunningScreen.h"

RunningScreen::RunningScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("running.layout");
    m_anim_enter = "None";
    m_anim_exit  = "None";
}

RunningScreen::~RunningScreen()
{
    // TODO Auto-generated destructor stub
}

void RunningScreen::exec()
{
    m_sig_transition.emit("crash");
}

