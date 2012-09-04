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

    m_chk_postProcess   = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_postProcess"));
    m_chk_cartoon       = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_cartoon"));
    m_chk_lighting      = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_lighting"));
    m_chk_patchGrids    = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_patchGrids"));
    m_chk_mainGrid      = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_mainGrid"));
    m_chk_gradientFloor = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_gradientFloor"));
    m_chk_logging       = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_logging"));
    m_chk_worldRotate   = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_worldRotate"));
    m_chk_participate   = static_cast<CEGUI::ToggleButton*>(
                            m_root->getChild("Panel/chk_participate"));
}

AdvancedScreen::~AdvancedScreen()
{

}

void AdvancedScreen::flushData()
{
    m_dataStore->get<bool>("adv:postProcess"  ) = m_chk_postProcess  ->isSelected();
    m_dataStore->get<bool>("adv:cartoon"      ) = m_chk_cartoon      ->isSelected();
    m_dataStore->get<bool>("adv:lighting"     ) = m_chk_lighting     ->isSelected();
    m_dataStore->get<bool>("adv:patchGrids"   ) = m_chk_patchGrids   ->isSelected();
    m_dataStore->get<bool>("adv:mainGrid"     ) = m_chk_mainGrid     ->isSelected();
    m_dataStore->get<bool>("adv:gradientFloor") = m_chk_gradientFloor->isSelected();
    m_dataStore->get<bool>("adv:logging"      ) = m_chk_logging      ->isSelected();
    m_dataStore->get<bool>("adv:worldRotate"  ) = m_chk_worldRotate  ->isSelected();
    m_dataStore->get<bool>("adv:participate"  ) = m_chk_participate  ->isSelected();
}

bool AdvancedScreen::onSave(const CEGUI::EventArgs &e)
{
    flushData();
    return true;
}


bool AdvancedScreen::onBack(const CEGUI::EventArgs &e)
{
    flushData();
    m_sig_transition.emit("paused");
    return true;
}

void AdvancedScreen::exec()
{
    m_chk_postProcess  ->setSelected(m_dataStore->get<bool>("adv:postProcess"  ));
    m_chk_cartoon      ->setSelected(m_dataStore->get<bool>("adv:cartoon"      ));
    m_chk_lighting     ->setSelected(m_dataStore->get<bool>("adv:lighting"     ));
    m_chk_patchGrids   ->setSelected(m_dataStore->get<bool>("adv:patchGrids"   ));
    m_chk_mainGrid     ->setSelected(m_dataStore->get<bool>("adv:mainGrid"     ));
    m_chk_gradientFloor->setSelected(m_dataStore->get<bool>("adv:gradientFloor"));
    m_chk_logging      ->setSelected(m_dataStore->get<bool>("adv:logging"      ));
    m_chk_worldRotate  ->setSelected(m_dataStore->get<bool>("adv:worldRotate"  ));
    m_chk_participate  ->setSelected(m_dataStore->get<bool>("adv:participate"  ));
}
