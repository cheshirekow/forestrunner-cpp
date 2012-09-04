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
        virtual void set_dispatcher(forestrunner::game::StateGraph* dispatcher);
        virtual void exec();

        void onScoreChanged(float score);
        void pause();
        void crash();
};

#endif /* RUNNINGSCREEN_H_ */
