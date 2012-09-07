/*
 *  \file   KeyboardGame.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/ios/InputHandler.h"

#include <cmath>
#include <OgreMath.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreSceneNode.h>

namespace forestrunner {
namespace          ios {

InputHandler::InputHandler()
{
    m_game      = 0;
    m_xSpeedMax = 20.0f;
    m_angle     = 0;
    m_maxAngle  = M_PI/4.0;
}

void InputHandler::setGame(Game* game)
{
    m_game = game;
}

void InputHandler::initRun()
{
    m_xSpeed2 = 0.0f;
}



void InputHandler::setAcceleration( double x, double y, double z )
{
    if( std::abs(m_angle) > m_maxAngle )
    {
        if(m_angle < 0)
            m_angle = -m_maxAngle;
        else
            m_angle = m_maxAngle;
    }
    m_game->setXSpeed( (m_angle / m_maxAngle)*m_xSpeedMax );

    // on a PC, we rotate the scene according to xspeed
    // on android, we do the opposite
    Ogre::Radian angle(m_angle);
    Ogre::Quaternion q(angle, Ogre::Vector3(0.0f,0.0f,1.0f) );

    m_game->setRotation(q);
}


}
}
