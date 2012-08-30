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




Application::Application():
    m_iosTimer(0)
{


}




Application::~Application()
{

}




bool Application::init()
{
    // instantiate the dummy logger so that it gets set as the singleton
    // for cegui (note: we're not using cegui anymore)
    // CEGUI::DummyLogger* guiLog = new CEGUI::DummyLogger();

    if (!setup())
        return false;

    m_iosTimer = OGRE_NEW Ogre::Timer();
    m_iosTimer->reset();

    mRoot->clearEventTimes();

    return true;
}




void Application::cleanup()
{
    tearDown();
}



} // namespace ios 
} // namespace forestrunner 
