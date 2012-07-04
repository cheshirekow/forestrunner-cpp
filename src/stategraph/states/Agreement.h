
/*
 *  @file   Agreement.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for Agreement class
 */

#ifndef FORESTRUNNER_STATEGRAPH_STATES_AGREEMENT_H
#define FORESTRUNNER_STATEGRAPH_STATES_AGREEMENT_H

#include "AnimatedPanel.h"
#include "stategraph/Button.h"

namespace   stategraph {
namespace       states {



/*
 *  @brief  No documentation yet
 *  @todo   write documentation for Agreement class
 */

class Agreement :
    public AnimatedPanel
{
    public:
        typedef Agreement       This_t;
        typedef AnimatedPanel   Base_t;

        sigc::signal<void,Manager&>  sig_agree;

    private:
        Button  m_btn_agree;
        Button  m_btn_disagree;

        void onAgree();
        void onDisagree();

    public:
        Agreement();
        virtual ~Agreement(){}

        /// overrides State::activate
        virtual void activate(Manager&);

        /// overrides State::deactivate
        virtual void deactivate(Manager&);

        virtual void innerUpdate(float tpf);

};





} //namespace states
} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_STATES_AGREEMENT_H


