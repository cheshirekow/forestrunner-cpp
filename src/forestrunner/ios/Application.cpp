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
 * Application.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: josh
 */

#include "forestrunner/ios/Application.h"

namespace forestrunner {
namespace          ios {




Application::Application(DataStore* store):
    Base_t(store),
    m_iosTimer(0)
{


}




Application::~Application()
{

}




bool Application::init(
        void* uiWindow, 
        void* uiView,
        void* uiViewController,
        unsigned int width,
        unsigned int height )
{
    // instantiate the dummy logger so that it gets set as the singleton
    // for cegui (note: we're not using cegui anymore)
    // CEGUI::DummyLogger* guiLog = new CEGUI::DummyLogger();

    m_uiWindow          = uiWindow;
    m_uiView            = uiView;
    m_uiViewController  = uiViewController;
    m_width             = width;
    m_height            = height;
    
    std::cout << "Initializing ios::Application with \n----------------"
        "\nuiWind: " << (void*)uiWindow << 
        "\nuiView: " << (void*)uiView <<
        "\n  uiVC: " << (void*)uiViewController <<
        "\n     w: " << width <<
        "\n     h: " << height <<
        std::endl; 

    if (!setup())
        return false;
        
    std::cout << "ios::Application setup finished" << std::endl;

    m_iosTimer = OGRE_NEW Ogre::Timer();
    m_iosTimer->reset();

    mRoot->clearEventTimes();

    return true;
}




bool Application::configure(void)
{
    m_pLog->logMessage(
            "setup: Finished setting up resources, configuring the root");

    std::stringstream strm;
    Ogre::NameValuePairList params;
    params["colourDepth"]          = "32";
    //m_params["externalGLControl"]    = "false";
    //m_params["externalGLContext"]    = "0";
    params["contentScalingFactor"] = "1.0";
    
    strm.str("");
    strm << (unsigned long)m_uiWindow;
    params["externalWindowHandle"] = strm.str();

    strm.str("");
    strm << (unsigned long)m_uiView;
    params["externalViewHandle"]   = strm.str();

    strm.str("");
    strm << (unsigned long)m_uiViewController;
    params["externalViewController"]  = strm.str();
    params["embeddedView"] = "true";
    
    // initialize, dont' create render window
    mRoot->initialise(false, "");

    // now create render window by attaching to the iOS UIView stuff
    mWindow = mRoot->createRenderWindow("ForestRunnerOgreWindow",m_width,m_height,true,&params);

    return true;
}




void Application::cleanup()
{
    tearDown();
}

bool Application::needsWork()
{
    return m_dispatchResult;
}

game::Dispatcher* Application::getDispatcher()
{
    return &m_dispatcher;
}

void Application::onProgress(float progress)
{
    m_cycleProgress = progress;
}

float Application::getProgress()
{
    return m_cycleProgress;
}

void Application::setupDispatcher()
{
    Base_t::setupDispatcher();
    
    m_dispatcher.initCycle.sig_progress.connect(
            sigc::mem_fun(*this,&Application::onProgress) );
    
    m_inputHandler.setGame(m_game);
}


float Application::getScore()
{
    return m_game->get_score();
}

void Application::setAcceleration(double acc[3])
{
    m_inputHandler.setAcceleration(acc);
}

void Application::setRoll( double roll )
{
    m_inputHandler.setRoll(roll);
}

} // namespace ios 
} // namespace forestrunner 
