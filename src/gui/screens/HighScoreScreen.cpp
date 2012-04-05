/*
 *  \file   HighScoreScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/HighScoreScreen.h"

HighScoreScreen::HighScoreScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("highscore.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChildRecursive("HighScore/Panel/btn_again");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onAgain,
                                this) );

    btn = m_root->getChildRecursive("HighScore/Panel/btn_difficulty");
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
    m_sig_transition.emit("countdown3");
}


bool HighScoreScreen::onChange(const CEGUI::EventArgs &e)
{
    m_sig_transition.emit("paused");
}

