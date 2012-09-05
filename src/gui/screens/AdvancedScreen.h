/*
 *  \file   AdvancedScreen.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef ADVANCEDSCREEN_H_
#define ADVANCEDSCREEN_H_

#include "gui/Screen.h"

class AdvancedScreen :
    public Screen
{
    private:
        CEGUI::ButtonBase*   m_btn_done;

        CEGUI::ToggleButton* m_chk_postProcess;
        CEGUI::ToggleButton* m_chk_cartoon;
        CEGUI::ToggleButton* m_chk_lighting;
        CEGUI::ToggleButton* m_chk_patchGrids;
        CEGUI::ToggleButton* m_chk_mainGrid;
        CEGUI::ToggleButton* m_chk_gradientFloor;
        CEGUI::ToggleButton* m_chk_logging;
        CEGUI::ToggleButton* m_chk_worldRotate;
        CEGUI::ToggleButton* m_chk_participate;

        std::vector<CEGUI::Window*> m_allWindows;
        sigc::connection    m_cnx;

        void disableAll();
        void enableAll();

    public:
        AdvancedScreen();
        virtual ~AdvancedScreen();

        bool onLightingChanged(const CEGUI::EventArgs &e);
        void onChangeCommitted();
        bool onBack(const CEGUI::EventArgs &e);

        void flushData();
        virtual void exec();
};

#endif /* ADVANCEDSCREEN_H_ */
