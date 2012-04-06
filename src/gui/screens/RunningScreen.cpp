/*
 *  \file   RunningScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/RunningScreen.h"
#include <game/Game.h>

RunningScreen::RunningScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("running.layout");
    m_anim_enter = "None";
    m_anim_exit  = "None";
}

RunningScreen::~RunningScreen()
{

}

void RunningScreen::set_game(Game* game)
{
    Screen::set_game(game);
    game->sig_stateChanged().connect(
            sigc::mem_fun(*this,&RunningScreen::onGameStateChanged) );
}

void RunningScreen::exec()
{
    m_game->setState(GS_RUNNING);
}

void RunningScreen::onGameStateChanged(GameState state)
{
    if(state == GS_CRASHED)
    {
        m_sig_transition.emit("crash");
    }
}
