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
#include "game/GameState.h"


InitScreen::InitScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadWindowLayout("initializing.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    m_pb_progress = m_root->getChildRecursive("Init/pb_progress");
}

InitScreen::~InitScreen()
{

}


void InitScreen::set_game(Game* game)
{
    Screen::set_game(game);

    game->sig_progressChanged().connect(
            sigc::mem_fun(*this,&InitScreen::onProgress) );
    game->sig_stateChanged().connect(
            sigc::mem_fun(*this,&InitScreen::onStateChanged) );
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

    m_game->setState(GS_INIT);
}

void InitScreen::onProgress(float progress)
{
    snprintf(m_cstr,6,"%4.2f",progress);
    m_pb_progress->setProperty("CurrentProgress",m_cstr);
}

void InitScreen::onStateChanged(GameState state)
{
    if(state == GS_COUNTDOWN)
        m_sig_transition.emit("countdown3");
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

