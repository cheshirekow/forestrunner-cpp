/*
 *  \file   RunningScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/RunningScreen.h"

#include <game/Game.h>
#include <cstring>

RunningScreen::RunningScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("running.layout");
    m_anim_enter = "None";
    m_anim_exit  = "None";

    m_txt_score = m_root->getChild("txt_score");
}

RunningScreen::~RunningScreen()
{

}

void RunningScreen::set_game(Game* game)
{
    Screen::set_game(game);
    game->sig_score.connect(
            sigc::mem_fun(*this,&RunningScreen::onScoreChanged) );
}

void RunningScreen::set_dispatcher(forestrunner::game::StateGraph* dispatcher)
{
    Screen::set_dispatcher(dispatcher);

    dispatcher->sig_crashed.connect(
            sigc::mem_fun(*this,&RunningScreen::crash) );
    dispatcher->sig_paused.connect(
            sigc::mem_fun(*this,&RunningScreen::pause) );
}


void RunningScreen::exec()
{
    //m_game->setState(GS_RUNNING);
    if( m_dispatcher->getState() == forestrunner::game::StateGraph::PAUSED )
        m_dispatcher->resumeFromPaused();
    else
        m_dispatcher->startNewRun();
}


void RunningScreen::pause()
{
    m_sig_transition.emit("paused");
}

void RunningScreen::crash()
{
    m_sig_transition.emit("crash");
}

void RunningScreen::onScoreChanged(float score)
{
    snprintf(m_cstr,20,"Score: %4.2f",score);
    m_txt_score->setProperty("Text",m_cstr);
}
