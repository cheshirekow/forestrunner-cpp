/*
 *  \file   InputHandler.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_IOS_INPUTHANDLER_H_
#define FORESTRUNNER_IOS_INPUTHANDLER_H_

#include "Game.h"

namespace forestrunner {
namespace          ios {

class InputHandler
{
    private:
        Game*   m_game;
        float   m_angle;
        float   m_maxAngle;
        float   m_xSpeedMax;
 
    public:
        InputHandler();

        void setGame(Game* game);
        void initRun();
        void setAcceleration( double x, double y, double z);
};

}
}

#endif /* KEYBOARDGAME_H_ */
