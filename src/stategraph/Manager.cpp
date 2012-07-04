
/*
 *  @file   Manager.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for Manager class
 */


#include "Manager.h"

namespace   stategraph {

Manager::Manager():
    m_viewport(0)
{}

void Manager::setViewport(Ogre::Viewport* viewport)
{
    m_viewport = viewport;
}

void Manager::update(float tpf)
{
    sig_update.emit(tpf,*this);
}



bool Manager::keyPressed( const OIS::KeyEvent &arg )
{
    sig_keyPressed.emit(arg,m_viewport);
    return false;
}


bool Manager::keyReleased( const OIS::KeyEvent &arg )
{
    sig_keyReleased.emit(arg,m_viewport);
    return false;
}



// OIS::MouseListener
bool Manager::mouseMoved( const OIS::MouseEvent &arg )
{
    sig_mouseMoved.emit(arg,m_viewport);
    return false;
}


bool Manager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    sig_mousePressed.emit(arg,m_viewport);
    return false;
}


bool Manager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    sig_mouseReleased.emit(arg,m_viewport);
    return false;
}



// OIS::MultiTouchListener
bool Manager::touchMoved( const OIS::MultiTouchEvent &arg )
{
    sig_touchMoved.emit(arg,m_viewport);
    return false;
}


bool Manager::touchPressed( const OIS::MultiTouchEvent &arg )
{
    sig_touchPressed.emit(arg,m_viewport);
    return false;
}


bool Manager::touchReleased( const OIS::MultiTouchEvent &arg )
{
    sig_touchReleased.emit(arg,m_viewport);
    return false;
}


bool Manager::touchCancelled( const OIS::MultiTouchEvent &arg )
{
    sig_touchCancelled.emit(arg,m_viewport);
    return false;
}







} //namespace stategraph



