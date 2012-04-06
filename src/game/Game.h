/*
 *  \file   Game.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef GAME_H_
#define GAME_H_

#include "GameState.h"
#include <OgreMath.h>
#include <OISKeyboard.h>

class Game
{
    protected:
        GameState   m_gameState;

        float   m_density;
        float   m_xAccel;
        float   m_xSpeedMax;
        float   m_xSpeed;
        float   m_ySpeed;
        float   m_radius;
        float   m_xPos;
        float   m_yPos;
        float   m_patchWidth;
        float   m_patchHeight;
        float   m_acSide;
        float   m_acRadius;
        float   m_acTrans;
        float   m_score;
        int     m_patchDimX;
        int     m_patchDimY;

    public:
        Ogre::SceneNode*    m_patchRoot;
        Ogre::SceneNode*    m_patchRotate;

    public:
        Game();
        virtual ~Game();

        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );

        virtual void update( Ogre::Real tpf );
        virtual void updateSpeed( Ogre::Real tpf )=0;
};

#endif /* GAME_H_ */
