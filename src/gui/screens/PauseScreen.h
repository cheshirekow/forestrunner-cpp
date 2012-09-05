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
    private:
        CEGUI::Window* m_btn_resume;
        CEGUI::Window* m_sb_speed;
        CEGUI::Window* m_sb_radius;
        CEGUI::Window* m_sb_density;

        bool             m_needsInit;
        sigc::connection m_initCnx;

    public:
        PauseScreen();
        virtual ~PauseScreen();

        /// read values from data store and set the sliders with those
        /// values
        virtual void exec();

        virtual void set_dispatcher( forestrunner::game::StateGraph* dispatcher);

        bool onSlider(const CEGUI::EventArgs &e);
        bool onResume(const CEGUI::EventArgs &e);
        bool onNewGame(const CEGUI::EventArgs &e);
        bool onAdvanced(const CEGUI::EventArgs &e);

        void onCrash();
        void onNewGameInitialized();
};

#endif /* PAUSESCREEN_H_ */
