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
    m_iStore    = 0;

    for(int j=0; j < 3; j++)
    {
        m_avg[j] = 0;
        for(int i=0; i < sm_nAverage; i++)
            m_store[j][i] = 0;
    }
}

void InputHandler::setGame(Game* game)
{
    m_game = game;
}

void InputHandler::initRun()
{
    m_angle = 0.0f;
}



void InputHandler::setAcceleration( double acc[3] )
{
    // every so often we recalculate the averages to avoid numerical drif
    if( ++m_iCalc > sm_recalcInterval )
    {
        m_iCalc = 0;
        for(int i=0; i < 3; i++)
        {
            m_avg[i]                = 0;
            m_store[i][m_iStore]    = acc[i];
            for(int j=0; j < sm_nAverage; j++)
                m_avg[i] += m_store[i][j] / sm_nAverage;
        }
    }
    else
    {
        for(int i=0; i < 3; i++)
        {
            m_avg[i]            -= m_store[i][m_iStore] / sm_nAverage;
            m_avg[i]            += acc[i] / sm_nAverage;
            m_store[i][m_iStore] = acc[i];
        }
    }

    /// wrap around the insert pointer
    if( ++m_iStore >= sm_nAverage )
        m_iStore = 0;

    float   xx = m_avg[0];
    float   yy = m_avg[1];

    // atan2 returns -PI to PI
    m_angle = atan2(yy, xx);

    if( std::abs(m_angle) > sm_maxAngle )
    {
        if(m_angle < 0)
            m_angle = -sm_maxAngle;
        else
            m_angle = sm_maxAngle;
    }
    m_game->setXSpeed( (m_angle / sm_maxAngle)*m_xSpeedMax );

    // on a PC, we rotate the scene according to xspeed
    // on android, we do the opposite
    Ogre::Radian angle(m_angle);
    Ogre::Quaternion q(angle, Ogre::Vector3(0.0f,0.0f,1.0f) );

    m_game->setRotation(q);
}


}
}
