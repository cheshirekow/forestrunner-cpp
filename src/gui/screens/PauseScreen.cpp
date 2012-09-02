/*
 *  \file   PauseScreen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "PauseScreen.h"
#include "game/Game.h"

PauseScreen::PauseScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("paused.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChild("Panel/btn_new");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onNewGame,
                                this) );

    btn = m_root->getChild("Panel/btn_resume");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onResume,
                                this) );

    btn = m_root->getChild("Panel/btn_advanced");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &PauseScreen::onAdvanced,
                                this) );

    m_sb_speed   = m_root->getChild("Panel/sb_speed");
    m_sb_radius  = m_root->getChild("Panel/sb_radius");
    m_sb_density = m_root->getChild("Panel/sb_density");

    m_sb_speed->subscribeEvent(
            CEGUI::Scrollbar::EventScrollPositionChanged,
            CEGUI::Event::Subscriber(
                    &PauseScreen::onSlider,
                    this) );

    m_sb_radius->subscribeEvent(
            CEGUI::Scrollbar::EventScrollPositionChanged,
            CEGUI::Event::Subscriber(
                    &PauseScreen::onSlider,
                    this) );

    m_sb_density->subscribeEvent(
            CEGUI::Scrollbar::EventScrollPositionChanged,
            CEGUI::Event::Subscriber(
                    &PauseScreen::onSlider,
                    this) );

}

PauseScreen::~PauseScreen()
{

}

void PauseScreen::exec()
{
    CEGUI::Scrollbar* sb;

    sb = static_cast<CEGUI::Scrollbar*>(m_sb_speed);
    sb->setScrollPosition( m_dataStore->get<int>("pref:velocity") );

    sb = static_cast<CEGUI::Scrollbar*>(m_sb_radius);
    sb->setScrollPosition( m_dataStore->get<int>("pref:radius") );

    sb = static_cast<CEGUI::Scrollbar*>(m_sb_density);
    sb->setScrollPosition( m_dataStore->get<int>("pref:density") );
}

bool PauseScreen::onSlider(const CEGUI::EventArgs& e)
{
    const CEGUI::WindowEventArgs& args =
            static_cast<const CEGUI::WindowEventArgs&>(e);
    CEGUI::Scrollbar* sb = static_cast<CEGUI::Scrollbar*>(args.window);

    int rounded = (int)std::floor(sb->getScrollPosition() + 0.5);
    sb->setScrollPosition( (float)rounded );

    if(args.window == m_sb_speed)
    {
        m_dataStore->get<int>("pref:velocity") = rounded;
        m_game->setSpeed(rounded);
    }
    if(args.window == m_sb_radius)
    {
        m_dataStore->get<int>("pref:radius") = rounded;
        m_game->setRadius(rounded);
    }
    if(args.window == m_sb_density)
    {
        m_dataStore->get<int>("pref:density") = rounded;
        m_game->setDensity(rounded);
    }

    return true;
}

bool PauseScreen::onResume(const CEGUI::EventArgs &e)
{
    m_dataStore->flush();
    m_sig_transition("running");
    return true;
}


bool PauseScreen::onNewGame(const CEGUI::EventArgs &e)
{
    m_dataStore->flush();
    m_sig_transition("init");
    return true;
}



bool PauseScreen::onAdvanced(const CEGUI::EventArgs &e)
{
    m_sig_transition("advanced");
    return true;
}



