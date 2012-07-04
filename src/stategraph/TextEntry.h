
/*
 *  @file   TextEntry.h
 *
 *  @date   Jul 04, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  Definition for TextEntry class
 */

#ifndef FORESTRUNNER_STATEGRAPH_TEXTENTRY_H
#define FORESTRUNNER_STATEGRAPH_TEXTENTRY_H


#include <map>
#include <sigc++/sigc++.h>
#include <OISKeyboard.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreOverlayElement.h>
#include "Manager.h"

namespace   stategraph {





/*
 *  @brief  No documentation yet
 *  @todo   write documentation for TextEntry class
 */

class TextEntry
{
    private:
        int                     m_maxChars;
        std::string             m_string;
        Ogre::OverlayElement*   m_textarea;

        std::map<Manager*,sigc::connection> m_connections;

    public:
        TextEntry( int maxChars, std::string default_val="Anon" );

        void setElement( Ogre::OverlayElement* textarea );

        void keyPressed( const OIS::KeyEvent& evt );

        void activate(Manager& mgr);
        void deactivate(Manager& mgr);

        sigc::slot<void, const OIS::KeyEvent&> slot_keyPressed();


};





} //namespace stategraph

#endif //def FORESTRUNNER_STATEGRAPH_TEXTENTRY_H


