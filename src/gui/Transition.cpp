/*
 *  \file   Transition.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "Transition.h"
#include <iostream>

Transition::Transition(CEGUI::Window* win_from,
                    const CEGUI::String& anim_exit,
                    CEGUI::Window* win_to,
                    const CEGUI::String& anim_enter):
    m_win_from(win_from),
    m_win_to(win_to)
{
    CEGUI::AnimationManager& mgr = CEGUI::AnimationManager::getSingleton();


    if(win_from)
    {
        m_anim_exit  = mgr.instantiateAnimation(anim_exit);
        m_anim_exit->setTargetWindow(win_from);
        m_anim_exit->setEventReceiver(this);
    }
    else
        m_anim_exit = 0;

    if(win_to)
    {
        m_anim_enter = mgr.instantiateAnimation(anim_enter);
        m_anim_enter->setTargetWindow(win_to);
        m_anim_enter->setEventReceiver(this);
    }
    else
        m_anim_enter = 0;

    if(m_anim_exit)
    {
        std::cerr << "Transition::c'tor : starting exit animation" << std::endl;
        m_anim_exit->start();
    }
    else
    {
        std::cerr << "Transition::c'tor : starting entrance animation" << std::endl;
        CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_win_to);
        m_anim_enter->start();
    }
}

Transition::~Transition()
{
    CEGUI::AnimationManager& mgr = CEGUI::AnimationManager::getSingleton();
    /*
    if(m_anim_exit)
        mgr.destroyAnimationInstance(m_anim_exit);
    if(m_anim_enter)
        mgr.destroyAnimationInstance(m_anim_enter);
     */
}


void Transition::fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace)
{
    if( eventNamespace != CEGUI::AnimationInstance::EventNamespace )
        return;

    if( name == CEGUI::AnimationInstance::EventAnimationEnded)
    {
        CEGUI::AnimationEventArgs& animArgs =
                static_cast<CEGUI::AnimationEventArgs&>(args);
        if( animArgs.instance == m_anim_exit )
        {
            std::cerr << "Transition::fireEvent : exit animation finished" << std::endl;
            CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_win_to);
            m_win_to->show();
            m_win_to->activate();
            // there seems to be a bug in CEGUI where the sheet isn't displayed
            // unless there's a mouse input here... so we'll fake one
            //CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
            m_anim_enter->start();
        }
        else
        {
            std::cerr << "Transition::fireEvent : entrance animation finished" << std::endl;
            m_sig_finished.emit();
        }
    }
}

sigc::signal<void>& Transition::sig_finished()
{
    return m_sig_finished;
}

