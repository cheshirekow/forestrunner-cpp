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
 * AppInterface.h
 *
 *  Created on: Aug 29, 2012
 *      Author: josh
 */

#ifndef FORESTRUNNER_IOS_APPINTERFACE_H_
#define FORESTRUNNER_IOS_APPINTERFACE_H_

#include "forestrunner/datastore/DataStore.h"
#include "forestrunner/game/Dispatcher.h"

namespace forestrunner {
namespace          ios {

class Application;

/// simply wraps an application object with a p-impl so that xcode doesn't
/// have to see anything OGRE
class AppInterface
{
    private:
        Application* m_impl;

    public:
        AppInterface(DataStore* store);
        ~AppInterface();

        bool init(  void* uiWindow,
                    void* uiView,
                    void* uiViewController,
                    unsigned int width,
                    unsigned int height );
        bool step();
        void cleanup();
        bool needsWork();

        game::Dispatcher* getDispatcher();
        float getProgress();
};

} // namespace ios 
} // namespace forestrunner 

#endif // APPINTERFACE_H_
