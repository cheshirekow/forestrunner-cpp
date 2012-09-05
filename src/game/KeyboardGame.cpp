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
    m_game      = 0;
    m_xSpeed2   = 0.0f;
    m_xAccel    = 50.0f;
    m_xSpeedMax = 20.0f;
    m_leftDown  = false;
    m_rightDown = false;

}

KeyboardGame::~KeyboardGame()
{


}

void KeyboardGame::setGame(Game* game)
{
    m_game = game;
}

void KeyboardGame::initRun()
{
    m_xSpeed2 = 0.0f;
}

bool KeyboardGame::keyPressed( const OIS::KeyEvent &arg )
{
    if( arg.key == OIS::KC_LEFT || arg.key == OIS::KC_A )
        m_leftDown = true;

    if( arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_D )
        m_rightDown = true;

    if( arg.key == OIS::KC_Q )
        m_game->sig_crashed.emit();

    if( arg.key == OIS::KC_ESCAPE )
        m_game->sig_paused.emit();

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
            m_xSpeed2 -= m_xAccel*tpf;
        if(m_rightDown)
            m_xSpeed2 += m_xAccel*tpf;
    }
    else
    {
        float sign  = m_xSpeed2 >= 0 ? 1 : -1;
        m_xSpeed2 -= sign*m_xAccel*tpf;
        float sign2 = m_xSpeed2 >= 0 ? 1 : -1;

        // avoid overshoot
        if( sign != sign2 )
            m_xSpeed2 = 0;
    }

    m_xSpeed2 = std::min(m_xSpeed2, m_xSpeedMax);
    m_xSpeed2 = std::max(m_xSpeed2, -m_xSpeedMax);

    m_game->setXSpeed(m_xSpeed2);

    // on a PC, we rotate the scene according to xspeed
    // on android, we do the opposite
    Ogre::Real   aReal = (float)(M_PI / 9.0f) * m_xSpeed2 / m_xSpeedMax;
    Ogre::Radian angle(aReal);
    Ogre::Quaternion q(angle, Ogre::Vector3(0.0f,0.0f,1.0f) );

    m_game->setRotation(q);
}
