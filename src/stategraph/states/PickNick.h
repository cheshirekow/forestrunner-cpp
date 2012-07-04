
/*
 *  @file   PickNick.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for PickNick class
 */

#ifndef FORESTRUNNER_STATEGRAPH_STATES_PICKNICK_H
#define FORESTRUNNER_STATEGRAPH_STATES_PICKNICK_H

#include "AnimatedPanel.h"
#include "stategraph/Button.h"
#include "stategraph/TextEntry.h"

namespace   stategraph {
namespace       states {





/*
 *  @brief  No documentation yet
 *  @todo   write documentation for PickNick class
 */

class PickNick:
    public AnimatedPanel
{
    public:
        typedef PickNick        This_t;
        typedef AnimatedPanel   Base_t;

        sigc::signal<void,Manager&>  sig_finished;

    private:
        Button      m_btn_finished;
        TextEntry   m_txt_nick;

        Ogre::OverlayElement* m_textArea;

        void onFinished();

    public:
        PickNick();
        virtual ~PickNick(){}

        /// overrides State::activate
        virtual void activate(Manager&);

        /// overrides State::deactivate
        virtual void deactivate(Manager&);

        /// overrides AnimatedPanel::setPanel
        virtual void setPanel(const char* overlay, const char* panel);

        virtual void innerUpdate(float tpf);

};





} //namespace states
} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_STATES_PICKNICK_H


