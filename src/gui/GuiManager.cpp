/*
 *  \file   GuiManager.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <iostream>

#include "GuiManager.h"
#include "game/Game.h"

#include "screens/AgreementScreen.h"
#include "screens/PauseScreen.h"
#include "screens/InitScreen.h"
#include "screens/AdvancedScreen.h"
#include "screens/CountdownScreen.h"
#include "screens/RunningScreen.h"
#include "screens/CrashScreen.h"
#include "screens/HighScoreScreen.h"

GuiManager::GuiManager(Game* game,
        forestrunner::DataStore* store,
        forestrunner::game::StateGraph* dispatcher):
    m_activeTransition(0),
    m_activeScreen(0)
{
    // initialize all the screens
    m_screenMap["agreement"]  = new AgreementScreen();
    m_screenMap["init"]       = new InitScreen();
    m_screenMap["paused"]     = new PauseScreen();
    m_screenMap["advanced"]   = new AdvancedScreen();
    m_screenMap["countdown3"] = new CountdownScreen(3);
    m_screenMap["countdown2"] = new CountdownScreen(2);
    m_screenMap["countdown1"] = new CountdownScreen(1);
    m_screenMap["running"]    = new RunningScreen();
    m_screenMap["crash"]      = new CrashScreen();
    m_screenMap["highscore"]  = new HighScoreScreen();

    // register the change request for each one of them
    ScreenMap_t::iterator iPair;
    for(iPair = m_screenMap.begin(); iPair != m_screenMap.end(); ++iPair)
    {
        Screen* screen = iPair->second;
        screen->sig_transition().connect(
                sigc::mem_fun(*this,&GuiManager::requestChange) );
        screen->set_game(game);
        screen->set_store(store);
        screen->set_dispatcher(dispatcher);
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
        std::cerr << "requested change to page " << pageKey << std::endl;
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
    std::cerr << "GuiManager::transitionFinished : transition has finished" << std::endl;
    delete m_activeTransition;
    m_activeTransition = 0;
    m_activeScreen->exec();
}
