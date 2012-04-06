/*
 *  \file   KeyboardGame.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef KEYBOARDGAME_H_
#define KEYBOARDGAME_H_

#include "Game.h"

class KeyboardGame :
    public Game
{
    private:
        bool m_leftDown;
        bool m_rightDown;

    public:
        KeyboardGame();
        virtual ~KeyboardGame();

        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );

        virtual void updateSpeed( Ogre::Real tpf );
};

#endif /* KEYBOARDGAME_H_ */
