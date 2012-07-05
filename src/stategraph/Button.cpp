
/*
 *  @file   Button.cpp
 *
 *  @date   Jul 04, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for Button class
 */


#include "Button.h"

namespace   stategraph {


Button::Button( int xmin, int ymin, int xmax, int ymax )
{
    m_min[0] = xmin;
    m_min[1] = ymin;
    m_max[0] = xmax;
    m_max[1] = ymax;
}

void Button::activate(Manager& mgr)
{
    m_mouseConn[&mgr] =
        mgr.sig_mousePressed.connect(slot_mousePressed());
    m_touchConn[&mgr] =
        mgr.sig_touchPressed.connect(slot_touchPressed());
}

void Button::deactivate(Manager& mgr)
{
    m_mouseConn[&mgr].disconnect();
    m_touchConn[&mgr].disconnect();
}

void Button::onMousePress(const OIS::MouseEvent& evt, Ogre::Viewport* viewport)
{
    int cx = viewport->getActualWidth() / 2;
    int cy = viewport->getActualHeight() / 2;

    if(     evt.state.X.abs > m_min[0] + cx
        &&  evt.state.X.abs < m_max[0] + cx
        &&  evt.state.Y.abs > m_min[1] + cy
        &&  evt.state.Y.abs < m_max[1] + cy )
    {
        sig_clicked.emit();
    }
    else
    {
        std::cout
        << "\n cx: " << cx
        << "\n cy: " << cy
        << "\n    " << evt.state.X.abs << " < " << m_min[0] + cx
        << "\n || " << evt.state.X.abs << " > " << m_max[0] + cx
        << "\n || " << evt.state.Y.abs << " < " << m_min[1] + cx
        << "\n || " << evt.state.Y.abs << " > " << m_max[1] + cx << std::endl;
    }
}

void Button::onTouchPress( const OIS::MultiTouchEvent& evt, Ogre::Viewport* viewport  )
{
    int cx = viewport->getActualWidth() / 2;
    int cy = viewport->getActualHeight() / 2;

    if(     evt.state.X.abs > m_min[0] + cx
        &&  evt.state.X.abs < m_max[0] + cx
        &&  evt.state.Y.abs > m_min[1] + cy
        &&  evt.state.Y.abs < m_max[1] + cy )
    {
        sig_clicked.emit();
    }
    else
    {
        std::cout
        << "\n cx: " << cx
        << "\n cy: " << cy
        << "\n    " << evt.state.X.abs << " < " << m_min[0] + cx
        << "\n || " << evt.state.X.abs << " > " << m_max[0] + cx
        << "\n || " << evt.state.Y.abs << " < " << m_min[1] + cx
        << "\n || " << evt.state.Y.abs << " > " << m_max[1] + cx << std::endl;
    }
}

Button::MouseSlot_t Button::slot_mousePressed()
{
    return sigc::mem_fun(*this,&Button::onMousePress);
}


Button::TouchSlot_t Button::slot_touchPressed()
{
    return sigc::mem_fun(*this,&Button::onTouchPress);
}







} //namespace stategraph



