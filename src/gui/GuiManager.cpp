/*
 *  \file   GuiManager.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "GuiManager.h"
#include "screens/AgreementScreen.h"
#include "screens/PauseScreen.h"
#include "screens/InitScreen.h"

GuiManager::GuiManager():
    m_activeTransition(0),
    m_activeScreen(0)
{
    // initialize all the screens
    m_screenMap["agreement"]  = new AgreementScreen();
    m_screenMap["init"]       = new InitScreen();
    m_screenMap["paused"]     = new PauseScreen();

    // register the change request for each one of them
    ScreenMap_t::iterator iPair;
    for(iPair = m_screenMap.begin(); iPair != m_screenMap.end(); ++iPair)
    {
        Screen* screen = iPair->second;
        screen->sig_transition().connect(
                sigc::mem_fun(*this,&GuiManager::requestChange) );
    }

    // set the first screen and transition into it
    requestChange("agreement");
}

GuiManager::~GuiManager()
{

}

void GuiManager::requestChange(const std::string& pageKey)
{
    if(m_activeTransition)
        return;
    else
    {
        CEGUI::Window* win_from, *win_to;

        assert( m_screenMap[pageKey] );
        m_activeTransition = new Transition(
                    m_activeScreen ? m_activeScreen->get_root() : 0,
                    m_activeScreen ? m_activeScreen->get_anim_exit() : "none",
                    m_screenMap[pageKey]->get_root(),
                    m_screenMap[pageKey]->get_anim_enter() );
        m_activeScreen = m_screenMap[pageKey];
        m_activeTransition->sig_finished().connect(
            sigc::mem_fun(*this,&GuiManager::transitionFinished) );
    }
}


void GuiManager::transitionFinished()
{
    delete m_activeTransition;
    m_activeTransition = 0;
}
