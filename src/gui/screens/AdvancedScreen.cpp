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
    /*
    btn = m_root->getChild("Panel/btn_save");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onSave,
                                this) );
    */
    btn = m_root->getChild("Panel/btn_back");
    m_allWindows.push_back(btn);
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onBack,
                                this) );



    m_btn_done = static_cast<CEGUI::ButtonBase*>(btn);

    btn = m_root->getChild("Panel/chk_postProcess");
    m_allWindows.push_back(btn);
    m_chk_postProcess   = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_cartoon");
    m_allWindows.push_back(btn);
    m_chk_cartoon       = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_lighting");
    m_allWindows.push_back(btn);
    m_chk_lighting      = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_patchGrids");
    m_allWindows.push_back(btn);
    m_chk_patchGrids    = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_mainGrid");
    m_allWindows.push_back(btn);
    m_chk_mainGrid      = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_gradientFloor");
    m_allWindows.push_back(btn);
    m_chk_gradientFloor = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_logging");
    m_allWindows.push_back(btn);
    m_chk_logging       = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_worldRotate");
    m_allWindows.push_back(btn);
    m_chk_worldRotate   = static_cast<CEGUI::ToggleButton*>(btn);

    btn = m_root->getChild("Panel/chk_participate");
    m_allWindows.push_back(btn);
    m_chk_participate   = static_cast<CEGUI::ToggleButton*>(btn);

    m_chk_lighting->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onLightingChanged,
                                this
                        ) );

    m_chk_cartoon->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged,
                        CEGUI::Event::Subscriber(
                                &AdvancedScreen::onCartoonChanged,
                                this
                        ) );


}

AdvancedScreen::~AdvancedScreen()
{

}



void AdvancedScreen::disableAll()
{
    for( std::vector<CEGUI::Window*>::iterator ipWindow = m_allWindows.begin();
            ipWindow != m_allWindows.end(); ipWindow++ )
    {
        (*ipWindow)->setEnabled(false);
    }
}

void AdvancedScreen::enableAll()
{
    for( std::vector<CEGUI::Window*>::iterator ipWindow = m_allWindows.begin();
            ipWindow != m_allWindows.end(); ipWindow++ )
    {
        (*ipWindow)->setEnabled(true);
    }


}

void AdvancedScreen::flushData()
{
    m_dataStore->get<bool>("adv:postProcess"  ) = m_chk_postProcess  ->isSelected();
    m_dataStore->get<bool>("adv:patchGrids"   ) = m_chk_patchGrids   ->isSelected();
    m_dataStore->get<bool>("adv:mainGrid"     ) = m_chk_mainGrid     ->isSelected();
    m_dataStore->get<bool>("adv:gradientFloor") = m_chk_gradientFloor->isSelected();
    m_dataStore->get<bool>("adv:logging"      ) = m_chk_logging      ->isSelected();
    m_dataStore->get<bool>("adv:worldRotate"  ) = m_chk_worldRotate  ->isSelected();
    m_dataStore->get<bool>("adv:participate"  ) = m_chk_participate  ->isSelected();
    m_dataStore->flush();
}

bool AdvancedScreen::onLightingChanged(const CEGUI::EventArgs &e)
{
    using namespace forestrunner::keys;

    std::cerr << "Advanced Screen: Lighting changed" << std::endl;

    // disable all input
    disableAll();

    // change the data store
    m_dataStore->get<bool>(ADV_LIGHTING) = m_chk_lighting->isSelected();
    m_dataStore->markChanged(ADV_LIGHTING);

    // now call the dispatcher and put it in the "set lighting" loop
    m_dispatcher->startLightingCycle();
    return true;
}

bool AdvancedScreen::onCartoonChanged(const CEGUI::EventArgs &e)
{
    using namespace forestrunner::keys;

    std::cerr << "Advanced Screen: Cartoon changed" << std::endl;

    // disable all input
    disableAll();

    // change the data store
    m_dataStore->get<bool>(ADV_CARTOON) = m_chk_cartoon->isSelected();
    m_dataStore->markChanged(ADV_CARTOON);

    // now call the dispatcher and put it in the "set lighting" loop
    m_dispatcher->startCartoonCycle();
    return true;
}

void AdvancedScreen::onChangeCommitted()
{
    std::cerr << "Advanced Screen: Changes committed" << std::endl;
    enableAll();
}


bool AdvancedScreen::onBack(const CEGUI::EventArgs &e)
{
    flushData();
    m_cnx.disconnect();
    m_sig_transition.emit("paused");
    return true;
}

void AdvancedScreen::exec()
{
    enableAll();
    m_cnx = m_dispatcher->sig_cycleFinished.connect(
                sigc::mem_fun(*this,&AdvancedScreen::onChangeCommitted) );

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
