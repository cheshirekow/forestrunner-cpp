/*
 *  \file   PauseScreen.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef PAUSESCREEN_H_
#define PAUSESCREEN_H_

#include "gui/Screen.h"

class PauseScreen :
    public Screen
{
    public:
        PauseScreen();
        virtual ~PauseScreen();

        bool onResume(const CEGUI::EventArgs &e);
        bool onNewGame(const CEGUI::EventArgs &e);
        bool onAdvanced(const CEGUI::EventArgs &e);

        virtual void exec();
};

#endif /* PAUSESCREEN_H_ */
