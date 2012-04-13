/*
 *  \file   HighScoreScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "HighScoreScreen.h"
#include "game/Game.h"

HighScoreScreen::HighScoreScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("highscore.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChild("Panel/btn_again");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onAgain,
                                this) );

    btn = m_root->getChild("Panel/btn_difficulty");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onChange,
                                this) );
}

HighScoreScreen::~HighScoreScreen()
{

}

bool HighScoreScreen::onAgain(const CEGUI::EventArgs &e)
{
    m_game->initRun();
    m_sig_transition.emit("countdown3");
    return true;
}


bool HighScoreScreen::onChange(const CEGUI::EventArgs &e)
{
    m_sig_transition.emit("paused");
    return true;
}

