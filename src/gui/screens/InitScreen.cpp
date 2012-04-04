/*
 *  \file   InitScreen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "InitScreen.h"

InitScreen::InitScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("initializing.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";
}

InitScreen::~InitScreen()
{

}

void InitScreen::exec()
{
    m_sig_transition.emit("paused");
}
