
/*
 *  @file   Button.h
 *
 *  @date   Jul 04, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for Button class
 */

#ifndef FORESTRUNNER_STATEGRAPH_BUTTON_H
#define FORESTRUNNER_STATEGRAPH_BUTTON_H

#include <map>
#include <sigc++/sigc++.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>
#include <OGRE/OgreViewport.h>
#include "Manager.h"


namespace   stategraph {





/*
 *  @brief  No documentation yet
 *  @todo   write documentation for Button class
 */

class Button
{
    private:
        int m_min[2];
        int m_max[2];

        std::map<Manager*,sigc::connection> m_mouseConn;
        std::map<Manager*,sigc::connection> m_touchConn;

    public:
        typedef sigc::slot<void,const OIS::MouseEvent&,Ogre::Viewport*>
                                                               MouseSlot_t;

       typedef sigc::slot<void,const OIS::MultiTouchEvent&,Ogre::Viewport*>
                                                               TouchSlot_t;

        sigc::signal<void>  sig_clicked;

    private:
        void onMousePress( const OIS::MouseEvent& evt,
                            Ogre::Viewport* viewport );

        void onTouchPress( const OIS::MultiTouchEvent& evt,
                            Ogre::Viewport* viewport );

    public:
        Button( int xmin, int ymin, int xmax, int ymax );

        void activate(Manager& mgr);
        void deactivate(Manager& mgr);

        MouseSlot_t    slot_mousePressed();
        TouchSlot_t    slot_touchPressed();


};





} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_BUTTON_H


