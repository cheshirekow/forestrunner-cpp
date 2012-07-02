
/*
 *  @file   Initialize.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for Initialize class
 */

#ifndef FORESTRUNNER_STATEGRAPH_STATES_INITIALIZE_H
#define FORESTRUNNER_STATEGRAPH_STATES_INITIALIZE_H

#include "AnimatedPanel.h"

namespace   stategraph {
namespace       states {





/*
 *  @brief  initialize screen, performs loading operations on the
 *          game and then transitions
 *  @todo   write documentation for Initialize class
 */

class Initialize :
    public AnimatedPanel
{
    public:
        typedef Initialize      This_t;
        typedef AnimatedPanel   Base_t;

    private:
        int                     m_step;
        static const int        s_lastStep=100;

        Ogre::OverlayElement*   m_circle;
        Ogre::OverlayElement*   m_rectangle;

    public:
        sigc::signal<void,Manager&> sig_finished;

    public:
        Initialize();
        virtual ~Initialize(){}

        virtual void innerUpdate(float tpf);


};





} //namespace states
} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_STATES_INITIALIZE_H


