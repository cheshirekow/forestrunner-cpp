
/*
 *  @file   State.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for State class
 */

#ifndef FORESTRUNNER_STATEGRAPH_STATE_H
#define FORESTRUNNER_STATEGRAPH_STATE_H

#include "Manager.h"

#include <map>
#include <sigc++/sigc++.h>

namespace   stategraph {





/*
 *  @brief  abstract base class for states in the state graph
 */
class State
{
    public:
        typedef State   This_t;

    protected:
        std::map<Manager*,sigc::connection> m_connections;

    public:
        virtual ~State(){}
        virtual void update(float tpf, Manager&)=0;

        virtual void activate(Manager&);
        virtual void deactivate(Manager&);

        sigc::slot<void,Manager&> slot_activate();

};





} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_STATE_H


