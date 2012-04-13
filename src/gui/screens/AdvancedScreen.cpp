/*
 *  \file   AdvancedScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "gui/screens/AdvancedScreen.h"

AdvancedScreen::AdvancedScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("advanced.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChild("Panel/btn_save");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onSave,
                                this) );

    btn = m_root->getChild("Panel/btn_back");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onBack,
                                this) );
}

AdvancedScreen::~AdvancedScreen()
{

}

bool AdvancedScreen::onSave(const CEGUI::EventArgs &e)
{
    return true;
}


bool AdvancedScreen::onBack(const CEGUI::EventArgs &e)
{
    m_sig_transition.emit("paused");
    return true;
}
