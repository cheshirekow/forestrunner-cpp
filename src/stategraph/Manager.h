
/*
 *  @file   Manager.h
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for Manager class
 */

#ifndef FORESTRUNNER_STATEGRAPH_MANAGER_H
#define FORESTRUNNER_STATEGRAPH_MANAGER_H

#include <set>
#include <sigc++/sigc++.h>

namespace   stategraph {





/*
 *  @brief  manages the state graph by keeping track of the set of states
 *          which are currently active
 */
class Manager
{
    public:
        /// signal is emitted once per frame. The set of connected slots
        /// represents the set of active states. Any state who has a slot
        /// connected to this signal is active.
        sigc::signal<void,float,Manager&>    sig_update;

    public:
        // frame handler,
        void update(float tpf);

};





} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_MANAGER_H


