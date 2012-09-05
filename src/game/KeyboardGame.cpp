/*
 *  \file   KeyboardGame.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "game/KeyboardGame.h"

#include <cmath>
#include <OgreMath.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreSceneNode.h>

KeyboardGame::KeyboardGame()
{
    m_leftDown = false;
    m_rightDown = false;

}

KeyboardGame::~KeyboardGame()
{


}

bool KeyboardGame::keyPressed( const OIS::KeyEvent &arg )
{
    if( arg.key == OIS::KC_LEFT || arg.key == OIS::KC_A )
        m_leftDown = true;

    if( arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_D )
        m_rightDown = true;

    if( arg.key == OIS::KC_Q )
        sig_crashed.emit();

    if( arg.key == OIS::KC_ESCAPE )
        sig_paused.emit();

    return true;
}


bool KeyboardGame::keyReleased( const OIS::KeyEvent &arg )
{
    if( arg.key == OIS::KC_LEFT || arg.key == OIS::KC_A )
        m_leftDown = false;
    if( arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_D )
        m_rightDown = false;

    return true;
}


void KeyboardGame::updateSpeed( Ogre::Real tpf )
{
    // update the xspeed if necessary
    if(m_leftDown || m_rightDown)
    {
        if(m_leftDown)
            m_xSpeed -= m_xAccel*tpf;
        if(m_rightDown)
            m_xSpeed += m_xAccel*tpf;
    }
    else
    {
        float sign  = m_xSpeed >= 0 ? 1 : -1;
        m_xSpeed -= sign*m_xAccel*tpf;
        float sign2 = m_xSpeed >= 0 ? 1 : -1;

        // avoid overshoot
        if( sign != sign2 )
            m_xSpeed = 0;
    }

    m_xSpeed = std::min(m_xSpeed, m_xSpeedMax);
    m_xSpeed = std::max(m_xSpeed, -m_xSpeedMax);

    // on a PC, we rotate the scene according to xspeed
    // on android, we do the opposite
    Ogre::Real   aReal = (float)(M_PI / 9.0f) * m_xSpeed / m_xSpeedMax;
    Ogre::Radian angle(aReal);
    Ogre::Quaternion q(angle, Ogre::Vector3(0.0f,0.0f,1.0f) );

    m_patchRotate->setOrientation(q);
}
