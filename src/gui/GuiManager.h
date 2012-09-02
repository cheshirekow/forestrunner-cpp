/*
 *  \file   GuiManager.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#include "Transition.h"
#include "Screen.h"
#include "forestrunner/datastore/DataStore.h"

#include <string>
#include <map>



class Game;

class GuiManager
{
    public:
        typedef std::map<std::string,Screen*>   ScreenMap_t;

    private:
        Transition*     m_activeTransition;
        Screen*         m_activeScreen;
        ScreenMap_t     m_screenMap;

    public:
        GuiManager(Game* game, forestrunner::DataStore* store);
        virtual ~GuiManager();

        void requestChange(const std::string& pageKey);
        void transitionFinished();
};

#endif /* GUIMANAGER_H_ */
