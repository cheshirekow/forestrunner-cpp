/*
 *  \file   InitScreen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "InitScreen.h"
#include "game/Game.h"
#include <iostream>
#include <cstring>


InitScreen::InitScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("initializing.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    m_pb_progress = m_root->getChild("pb_progress");
}

InitScreen::~InitScreen()
{

}


void InitScreen::set_game(Game* game)
{
    Screen::set_game(game);

//    game->sig_progressChanged().connect(
//            sigc::mem_fun(*this,&InitScreen::onProgress) );
//    game->sig_stateChanged().connect(
//            sigc::mem_fun(*this,&InitScreen::onStateChanged) );
}



void InitScreen::set_dispatcher(forestrunner::game::StateGraph* dispatcher)
{
    Screen::set_dispatcher(dispatcher);

}



void InitScreen::exec()
{
    /*
    CEGUI::AnimationManager& mgr = CEGUI::AnimationManager::getSingleton();
    CEGUI::AnimationInstance* anim = mgr.instantiateAnimation("FakeProgress");
    anim->setTargetWindow(m_pb_progress);
    anim->setEventReceiver(this);
    anim->start();
    */

    std::back_insert_iterator<std::vector<sigc::connection> > cnx =
                                                std::back_inserter(m_cnx);

    cnx = m_dispatcher->initCycle.sig_progress.connect(
                        sigc::mem_fun(*this,&InitScreen::onProgress) );

    cnx = m_dispatcher->sig_cycleFinished.connect(
                        sigc::mem_fun(*this,&InitScreen::cycleFinished) );

//    m_game->setState(GS_INIT);
    m_needsInitCycle = false;
    m_needsInitRun   = false;
    m_game->readSettings(m_dataStore,m_needsInitCycle,m_needsInitRun);

    // FIXME: this is only to make sure that init happens, at some point
    // move this to the front of the program
    m_needsInitCycle = true;
    m_needsInitRun   = true;

    if(m_needsInitCycle)
        m_dispatcher->startInitCycle();
    else if(m_needsInitRun)
        m_dispatcher->startInitRun();
    else
        advance();
}

void InitScreen::onProgress(float progress)
{
    snprintf(m_cstr,6,"%4.2f",progress);
    m_pb_progress->setProperty("CurrentProgress",m_cstr);
}


void InitScreen::cycleFinished()
{
    // if needsInitCycle is true then that is the cycle that
    // just finished
    if(m_needsInitCycle)
    {
        std::cerr << "Init Cycle Finished" << std::endl;
        m_needsInitCycle = false;
        if(m_needsInitRun)
        {
            std::cerr << "Dispatching init Run" << std::endl;
            m_dispatcher->startInitRun();
        }
        else
        {
            std::cerr << "transitioning to countdown 3" << std::endl;
            advance();
        }
    }
    // otherwise it's the init run cycle which is finished
    else
    {
        std::cerr << "Init Run Finished" << std::endl;
        advance();
    }
}


void InitScreen::fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace)
{
    std::cout << "progress animation event fired" << std::endl;
    if( eventNamespace != CEGUI::AnimationInstance::EventNamespace )
        return;

    if( name == CEGUI::AnimationInstance::EventAnimationEnded )
    {
        CEGUI::AnimationEventArgs& animArgs =
                static_cast<CEGUI::AnimationEventArgs&>(args);
        CEGUI::AnimationManager& mgr =
                CEGUI::AnimationManager::getSingleton();

        std::cout << "progress animation complete" << std::endl;
        mgr.destroyAnimationInstance(animArgs.instance);
        m_sig_transition.emit("countdown3");
    }
}

void InitScreen::advance()
{
    for(int i=0; i < m_cnx.size(); i++)
        m_cnx[i].disconnect();

    m_cnx.clear();
    m_sig_transition.emit("paused");

}

