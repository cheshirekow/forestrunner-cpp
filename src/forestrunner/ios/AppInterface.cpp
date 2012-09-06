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
 * AppInterface.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: josh
 */

#include "forestrunner/ios/AppInterface.h"
#include "forestrunner/ios/Application.h"

namespace forestrunner {
namespace          ios {




AppInterface::AppInterface(DataStore* store)
{

try 
{
    m_impl = new Application(store);
} 
catch (std::exception& e) 
{
    std::cerr << "Failed to create ios::Application: " << e.what() << std::endl; 
}

}


AppInterface::~AppInterface()
{
    delete m_impl;
}



bool AppInterface::init(
        void* uiWindow,
        void* uiView,
        void* uiViewController,
        unsigned int width,
        unsigned int height )
{
    return m_impl->init(uiWindow,uiView,uiViewController,width,height);
}




bool AppInterface::step()
{
    return m_impl->step();
}




void AppInterface::cleanup()
{
    m_impl->cleanup();
}

bool AppInterface::needsWork()
{
    return m_impl->needsWork();
}


game::Dispatcher* AppInterface::getDispatcher()
{
    return m_impl->getDispatcher();
}

float AppInterface::getProgress()
{
    return m_impl->getProgress();
}

float AppInterface::getScore()
{
    return m_impl->getScore();
}


} // namespace ios 
} // namespace forestrunner 
