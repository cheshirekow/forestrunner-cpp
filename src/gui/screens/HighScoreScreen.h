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

class HighScoreScreen :
    public Screen
{
    public:
        HighScoreScreen();
        virtual ~HighScoreScreen();

        bool onAgain(const CEGUI::EventArgs &e);
        bool onChange(const CEGUI::EventArgs &e);
};

#endif /* HIGHSCORESCREEN_H_ */
