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

    std::cout << "in Transition c'tor" << std::endl;

    if(win_from)
    {
        std::cout << "adding exit animation" + anim_exit << std::endl;
        m_anim_exit  = mgr.instantiateAnimation(anim_exit);
        m_anim_exit->setTargetWindow(win_from);
        m_anim_exit->setEventReceiver(this);
    }
    else
        m_anim_exit = 0;

    if(win_to)
    {
        std::cout << "adding entrance animation" + anim_enter << std::endl;
        m_anim_enter = mgr.instantiateAnimation(anim_enter);
        m_anim_enter->setTargetWindow(win_to);
        m_anim_enter->setEventReceiver(this);
    }
    else
        m_anim_enter = 0;

    if(m_anim_exit)
        m_anim_exit->start();
    else
    {
        CEGUI::System::getSingleton().setGUISheet(m_win_to);
        m_anim_enter->start();
    }
}

Transition::~Transition()
{
    CEGUI::AnimationManager& mgr = CEGUI::AnimationManager::getSingleton();
    if(m_anim_exit)
        mgr.destroyAnimationInstance(m_anim_exit);
    if(m_anim_enter)
        mgr.destroyAnimationInstance(m_anim_enter);
}


void Transition::fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace)
{
    std::cout << "transition event fired" << std::endl;
    if( eventNamespace != CEGUI::AnimationInstance::EventNamespace )
    {
        std::cout << "but it doesn't fit the namespace" << std::endl;
        return;
    }

    if( name == CEGUI::AnimationInstance::EventAnimationEnded )
    {
        CEGUI::AnimationEventArgs& animArgs =
                static_cast<CEGUI::AnimationEventArgs&>(args);
        if( animArgs.instance == m_anim_exit )
        {
            std::cout << "   the exit is finished" << std::endl;
            CEGUI::System::getSingleton().setGUISheet(m_win_to);
            m_anim_enter->start();
        }
        else
        {
            std::cout << "   the entrance is finished" << std::endl;
            m_sig_finished.emit();
        }
    }
}

sigc::signal<void>& Transition::sig_finished()
{
    return m_sig_finished;
}

