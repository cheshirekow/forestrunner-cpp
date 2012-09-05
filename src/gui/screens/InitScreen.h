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
        char            m_cstr[6];

        bool    m_needsInitCycle;
        bool    m_needsInitRun;

    public:
        InitScreen();
        virtual ~InitScreen();

        virtual void set_game(Game* game);
        virtual void set_dispatcher(forestrunner::game::StateGraph* dispatcher);
        virtual void exec();
        virtual void fireEvent (const CEGUI::String &name,
                                    CEGUI::EventArgs &args,
                                    const CEGUI::String &eventNamespace="");

        void onProgress(float progress);
        void initCycleFinished();
        void initRunFinished();
};

#endif /* INITSCREEN_H_ */
