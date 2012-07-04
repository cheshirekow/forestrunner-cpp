
/*
 *  @file   TextEntry.cpp
 *
 *  @date   Jul 04, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for TextEntry class
 */


#include "TextEntry.h"

namespace   stategraph {



TextEntry::TextEntry(int maxChars, std::string default_val)
{
    m_maxChars = maxChars;
    m_string   = default_val;
}

void TextEntry::setElement(Ogre::OverlayElement* textarea)
{
    m_textarea = textarea;
}

void TextEntry::keyPressed(const OIS::KeyEvent& evt)
{
    if(     (OIS::KC_1 <= evt.key && evt.key <= OIS::KC_0)
        ||  (OIS::KC_Q <= evt.key && evt.key <= OIS::KC_P)
        ||  (OIS::KC_A <= evt.key && evt.key <= OIS::KC_L)
        ||  (OIS::KC_Z <= evt.key && evt.key <= OIS::KC_M)
        ||  (evt.key == OIS::KC_SPACE)
        ||  (evt.key == OIS::KC_UNDERLINE))
    {
        m_string += (char)evt.text;
    }

    if( evt.key == OIS::KC_BACK )
        m_string = m_string.substr(0,m_string.size()-1);

    m_textarea->setCaption(m_string.c_str());
}

void TextEntry::activate(Manager& mgr)
{
    m_connections[&mgr] =
            mgr.sig_keyPressed.connect( sigc::hide(
                    slot_keyPressed() ));
}

void TextEntry::deactivate(Manager& mgr)
{
    m_connections[&mgr].disconnect();
}

sigc::slot<void, const OIS::KeyEvent&> TextEntry::slot_keyPressed()
{
    return sigc::mem_fun(*this,&TextEntry::keyPressed);
}


} //namespace stategraph



