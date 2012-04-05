/*
 *  \file   PauseScreen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "PauseScreen.h"

PauseScreen::PauseScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("paused.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChildRecursive("Pause/Panel/btn_new");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onNewGame,
                                this) );

    btn = m_root->getChildRecursive("Pause/Panel/btn_resume");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onResume,
                                this) );

    btn = m_root->getChildRecursive("Pause/Panel/btn_advanced");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onAdvanced,
                                this) );
}

PauseScreen::~PauseScreen()
{

}

bool PauseScreen::onResume(const CEGUI::EventArgs &e)
{
    m_sig_transition("running");
    return true;
}


bool PauseScreen::onNewGame(const CEGUI::EventArgs &e)
{
    m_sig_transition("running");
    return true;
}



bool PauseScreen::onAdvanced(const CEGUI::EventArgs &e)
{
    m_sig_transition("advanced");
    return true;
}



