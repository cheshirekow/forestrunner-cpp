/*
 *  \file   Transition.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <CEGUI/CEGUI.h>
#include <sigc++/sigc++.h>

class Transition :
    public CEGUI::EventSet
{
    private:
        CEGUI::Window*              m_win_from;
        CEGUI::Window*              m_win_to;
        CEGUI::AnimationInstance*   m_anim_exit;
        CEGUI::AnimationInstance*   m_anim_enter;
        sigc::signal<void>          m_sig_finished;

    public:
        Transition( CEGUI::Window* win_from,
                    const CEGUI::String& anim_exit,
                    CEGUI::Window* win_to,
                    const CEGUI::String& anim_enter);

        virtual ~Transition();

        virtual void    fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace="");

        sigc::signal<void>& sig_finished();
};

#endif /* TRANSITION_H_ */
