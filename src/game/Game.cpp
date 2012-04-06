/*
 *  \file   Game.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "Game.h"

#include <cmath>
#include <OgreSceneNode.h>

Game::Game()
{
    m_gameState = GS_CRASHED;

    m_xAccel    = 10.0f;
    m_xSpeedMax = 6.0f;
    m_xSpeed    = 0.0f;
    m_ySpeed    = 3.0f;
    m_density   = 20.0f;
    m_radius    = 0.1f;

    m_xPos      = 0;
    m_yPos      = 0;
    m_patchWidth    = 5.1f; //20.1f;
    m_patchHeight   = 5.1f; //20.1f;

    m_patchDimX = 5;
    m_patchDimY = 8; //4;

    m_acSide    = 0.3f;
    m_acRadius  = (m_acSide/2.0f) * (float)std::tan(M_PI/6.0);
    m_acTrans   = (float)( m_acSide*std::sin(M_PI/3) ) - m_acRadius;
}

Game::~Game()
{

}

GameState Game::getState()
{
    return m_gameState;
}

void Game::setState(GameState state)
{
    m_gameState = state;

    if(state == GS_INIT)
    {
        m_init_i = 0;
        m_init_j = 0;
    }

}

bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    return true;
}

bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}

void Game::stepInit()
{
    // m_patch[m_init_i][m_init_j]->rebuild();

    if( ++m_init_j > m_patchDimY )
    {
        m_init_j=0;
        if( ++m_init_i > m_patchDimX )
            internal_setState(GS_COUNTDOWN);
    }

    m_sig_progressChanged.emit(
        (m_init_i*m_patchDimY + m_init_j) /
            ((float)(m_patchDimX * m_patchDimY))
        );
}

void Game::update( Ogre::Real tpf )
{
    if(m_gameState == GS_INIT)
        stepInit();

    if(m_gameState != GS_RUNNING)
        return;

    m_score += tpf;
    m_sig_scoreChanged.emit(m_score);
    updateSpeed(tpf);

    m_yPos += m_ySpeed*tpf;
    m_xPos -= m_xSpeed*tpf;

    if(m_xPos > m_patchWidth)
        m_xPos -= m_patchWidth;
    if(m_xPos < -m_patchWidth)
        m_xPos += m_patchWidth;

    if(m_yPos > m_patchHeight)
        m_yPos -= m_patchHeight;

    m_patchRoot->setPosition(m_xPos,0,m_yPos);
}


sigc::signal<void,GameState>& Game::sig_stateChanged()
{
    return m_sig_stateChanged;
}

sigc::signal<void,float>& Game::sig_scoreChanged()
{
    return m_sig_scoreChanged;
}

sigc::signal<void,float>& Game::sig_progressChanged()
{
    return m_sig_progressChanged;
}


void Game::internal_setState(GameState state)
{
    m_gameState = state;
    m_sig_stateChanged.emit(state);
}
