/*
 *  \file   RunningScreen.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef RUNNINGSCREEN_H_
#define RUNNINGSCREEN_H_

#include "gui/Screen.h"
#include "game/GameState.h"

class RunningScreen :
    public Screen
{
    private:
        CEGUI::Window*  m_txt_score;
        char            m_cstr[20];

    public:
        RunningScreen();
        virtual ~RunningScreen();

        virtual void set_game(Game* game);
        virtual void exec();

        void onGameStateChanged(GameState state);
        void onScoreChanged(float score);
};

#endif /* RUNNINGSCREEN_H_ */
