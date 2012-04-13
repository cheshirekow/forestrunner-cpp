/*
 *  \file   CrashScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/CrashScreen.h"

CrashScreen::CrashScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("crash.layout");
    m_anim_enter = "PulseIn";
    m_anim_exit  = "PulseOut";

}

CrashScreen::~CrashScreen()
{

}

void CrashScreen::exec()
{
    m_sig_transition.emit("highscore");
}
