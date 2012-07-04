
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

#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>

#include <OGRE/OgreViewport.h>

namespace   stategraph {





/*
 *  @brief  manages the state graph by keeping track of the set of states
 *          which are currently active
 */
class Manager :
    public OIS::KeyListener,
    public OIS::MouseListener,
    public OIS::MultiTouchListener
{
    private:
        Ogre::Viewport* m_viewport;

    public:
        typedef sigc::signal<void, const OIS::KeyEvent&, Ogre::Viewport*>
                                                                KeySignal_t;

        typedef sigc::signal<void, const OIS::MouseEvent&, Ogre::Viewport*>
                                                                MouseSignal_t;

        typedef sigc::signal<void, const OIS::MultiTouchEvent&, Ogre::Viewport*>
                                                                TouchSignal_t;

        /// signal is emitted once per frame. The set of connected slots
        /// represents the set of active states. Any state who has a slot
        /// connected to this signal is active.
        sigc::signal<void,float,Manager&>    sig_update;

        KeySignal_t sig_keyPressed;
        KeySignal_t sig_keyReleased;

        MouseSignal_t sig_mouseMoved;
        MouseSignal_t sig_mousePressed;
        MouseSignal_t sig_mouseReleased;

        TouchSignal_t sig_touchMoved;
        TouchSignal_t sig_touchPressed;
        TouchSignal_t sig_touchReleased;
        TouchSignal_t sig_touchCancelled;

    public:
        Manager();
        void setViewport(Ogre::Viewport* viewport);

        // frame handler,
        void update(float tpf);

        // OIS::KeyListener
        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );

        // OIS::MouseListener
        virtual bool mouseMoved( const OIS::MouseEvent &arg );
        virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

        // OIS::MultiTouchListener
        virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
        virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
        virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
        virtual bool touchCancelled( const OIS::MultiTouchEvent &arg );

};





} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_MANAGER_H


