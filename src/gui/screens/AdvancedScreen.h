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
    public:
        AdvancedScreen();
        virtual ~AdvancedScreen();

        bool onSave(const CEGUI::EventArgs &e);
        bool onBack(const CEGUI::EventArgs &e);
};

#endif /* ADVANCEDSCREEN_H_ */
