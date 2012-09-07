/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of forestrunner.
 *
 *  forestrunner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  forestrunner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with forestrunner.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * Application.h
 *
 *  Created on: Aug 29, 2012
 *      Author: josh
 */

#ifndef FORESTRUNNER_IOS_APPLICATION_H_
#define FORESTRUNNER_IOS_APPLICATION_H_

#include "forestrunner/Application.h"
#include "forestrunner/datastore/DataStore.h"
#include "forestrunner/ios/InputHandler.h"

namespace forestrunner {
namespace          ios {

class Application:
    public forestrunner::Application
{
    public:
        typedef forestrunner::Application Base_t;

    protected:
        Ogre::Timer*        m_iosTimer;

        void*               m_uiWindow;
        void*               m_uiView;
        void*               m_uiViewController;
        unsigned int        m_width;
        unsigned int        m_height;
        
        /// iOS can't use the sigc++ callbacks so we'll store the info here
        float               m_cycleProgress;

        InputHandler        m_inputHandler;

    public:
        Application(DataStore* store);
        virtual ~Application();

        /// calls setup and initializes the system
        bool init(  void* uiWindow, 
                    void* uiView,
                    void* uiViewController,
                    unsigned int width,
                    unsigned int height );

        /// overrides base class configure to pass handle to UIView and
        /// UIViewController, instead of loading the configuration window,
        bool configure();

        /// performs one step of the render loop
        /// bool step();

        /// does cleanup
        void cleanup();

        /// returns true if the current cycle is still working
        bool needsWork();

        /// return dispatcher interface
        game::Dispatcher* getDispatcher();
        
        void onProgress(float progress);
        
        float getProgress();
        
        virtual void setupDispatcher();
        
        float getScore();

        void setAcceleration( double acc[3]);
        void setRoll( double roll );
};

} // namespace ios 
} // namespace forestrunner 

#endif // APPLICATION_H_
