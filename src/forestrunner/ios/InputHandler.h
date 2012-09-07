/*
 *  \file   InputHandler.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_IOS_INPUTHANDLER_H_
#define FORESTRUNNER_IOS_INPUTHANDLER_H_

#include "game/Game.h"

namespace forestrunner {
namespace          ios {

class InputHandler
{
    private:
        static const int   sm_recalcInterval = 10;
        static const int   sm_nAverage       = 3;
        static const float sm_maxAngle;

    private:
        Game*   m_game;
        float   m_angle;
        float   m_xSpeedMax;

        int     m_iCalc;        ///< how long since we last recalculated
                                ///  average
        int     m_iStore;       ///< current write index of angle store

        /// storeage for low pass filtering
        float   m_avg[3];
        float   m_store[3][sm_nAverage];
 
    public:
        InputHandler();

        void setGame(Game* game);
        void initRun();
        void setAcceleration( double acc[3] );
};

}
}

#endif /* KEYBOARDGAME_H_ */
