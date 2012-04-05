/*
 *  \file   AgreementScreen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "AgreementScreen.h"

AgreementScreen::AgreementScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("agreement.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChildRecursive("Agreement/Panel/btn_accept");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &AgreementScreen::onAccept,
                                this) );
}

AgreementScreen::~AgreementScreen()
{

}

bool AgreementScreen::onAccept(const CEGUI::EventArgs &e)
{
    m_sig_transition.emit("paused");
    return true;
}

