/*
 *  \file   InitScreen.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef INITSCREEN_H_
#define INITSCREEN_H_

#include "gui/Screen.h"

class InitScreen :
    public Screen,
    public CEGUI::EventSet
{
    private:
        CEGUI::Window*  m_pb_progress;

    public:
        InitScreen();
        virtual ~InitScreen();

        virtual void exec();
        virtual void    fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace="");
};

#endif /* INITSCREEN_H_ */
