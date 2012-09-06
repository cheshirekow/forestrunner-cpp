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
    m_btn_again = btn;

    btn = m_root->getChild("Panel/btn_difficulty");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onChange,
                                this) );
    m_btn_difficulty = btn;
}

HighScoreScreen::~HighScoreScreen()
{

}

void HighScoreScreen::disableAll()
{
    m_btn_again     ->setEnabled(false);
    m_btn_difficulty->setEnabled(false);

}

void HighScoreScreen::enableAll()
{
    m_btn_again     ->setEnabled(true);
    m_btn_difficulty->setEnabled(true);
}

bool HighScoreScreen::onAgain(const CEGUI::EventArgs &e)
{
    disableAll();
    m_cnx = m_dispatcher->sig_cycleFinished.connect(
            sigc::mem_fun(*this,&HighScoreScreen::onInitFinished) );
    m_dispatcher->startInitRun();
    return true;
}


bool HighScoreScreen::onChange(const CEGUI::EventArgs &e)
{
    disableAll();
    m_sig_transition.emit("paused");
    return true;
}

void HighScoreScreen::exec()
{
    m_dataStore->write_score(m_game->get_score());
    enableAll();
}


void HighScoreScreen::onInitFinished()
{
    m_cnx.disconnect();
    m_sig_transition.emit("countdown3");
}
