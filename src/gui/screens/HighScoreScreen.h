/*
 *  \file   HighScoreScreen.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HIGHSCORESCREEN_H_
#define HIGHSCORESCREEN_H_

#include "gui/Screen.h"
#include "forestrunner/util/Printf.h"

class HighScoreScreen :
    public Screen
{
    private:
        forestrunner::util::Printf m_printf;

        sigc::connection m_cnx;

        CEGUI::Listbox* m_lb_userScores;
        CEGUI::Listbox* m_lb_globalScores;
        CEGUI::Window*  m_btn_again;
        CEGUI::Window*  m_btn_difficulty;

        void disableAll();
        void enableAll();

    public:
        HighScoreScreen();
        virtual ~HighScoreScreen();

        bool onAgain(const CEGUI::EventArgs &e);
        bool onChange(const CEGUI::EventArgs &e);

        virtual void exec();

        void onInitFinished();
};

#endif /* HIGHSCORESCREEN_H_ */
