
/*
 *  @file   AnimatedPanel.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for AnimatedPanel class
 */

#ifndef FORESTRUNNER_STATEGRAPH_STATES_ANIMATEDPANEL_H
#define FORESTRUNNER_STATEGRAPH_STATES_ANIMATEDPANEL_H

#include "../State.h"
#include <Ogre.h>

namespace   stategraph {
namespace       states {


/*
 *  @brief  No documentation yet
 *  @todo   write documentation for AnimatedPanel class
 */

class AnimatedPanel:
    public State
{
    public:
        enum AnimationStyle
        {
            STYLE_FLY,
            STYLE_PULSE
        };

    protected:
        typedef sigc::signal<void,Manager&> ExitSignal_t;

        Ogre::Overlay*              m_overlay;
        Ogre::OverlayContainer*     m_panel;
        ExitSignal_t*               m_exitSignal;
        int                         m_step;

        float   m_t;
        float   m_m;
        float   m_duration;

        float   m_topTarget;
        float   m_topAbove;
        float   m_topBelow;

    protected:
        void exit(ExitSignal_t* sig);

    public:
        AnimatedPanel();
        virtual ~AnimatedPanel(){}

        virtual void setPanel(const char* overlay, const char* panel);
        virtual void update(float tpf, Manager& mgr);
        virtual void innerUpdate(float tpf)=0;



};





} //namespace states
} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_STATES_ANIMATEDPANEL_H


