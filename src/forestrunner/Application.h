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


#ifndef FORESTRUNNER_APPLICATION_H
#define FORESTRUNNER_APPLICATION_H

#include <Ogre.h>

#include "game/Game.h"
#include "forestrunner/datastore/DataStore.h"
#include "forestrunner/game/StateGraph.h"

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// dx10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  endif
#  if OGRE_VERSION >= 0x10800
#    if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#      define OGRE_IS_IOS 1
#    endif
#  else
#    if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
#      define OGRE_IS_IOS 1
#    endif
#  endif
#  ifdef OGRE_IS_IOS
#    undef OGRE_STATIC_CgProgramManager
#    undef OGRE_STATIC_GL
#    define OGRE_STATIC_GLES 1
#    ifdef OGRE_USE_GLES2
#      define OGRE_STATIC_GLES2 1
#      define USE_RTSHADER_SYSTEM
#      undef OGRE_STATIC_GLES
#    endif
#    ifdef __OBJC__
#      import <UIKit/UIKit.h>
#    endif
#  endif
#  include "OgreStaticPluginLoader.h"
#endif


namespace forestrunner {


class Application :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public Ogre::RenderQueueListener
{

public:
    /// does nothing but initialize pointers to null and assigns the value of
    /// the resource path
    Application(DataStore* store);

    /// cleans up the window listener interface
    virtual ~Application();

    /// prcesses the message queue, then renders one frame
    virtual bool step();

protected:
    Ogre::Root*             mRoot;
    Ogre::Camera*           mCamera;
    Ogre::SceneManager*     mSceneMgr;
    Ogre::RenderWindow*     mWindow;
    Ogre::Viewport*         mViewport;
    Ogre::Log*              m_pLog;
    Ogre::String            m_ResourcePath;
    Ogre::String            mResourcesCfg;
    Ogre::String            mPluginsCfg;

    bool mCursorWasVisible;  // was cursor visible before dialog appeared
    bool mShutDown;
    bool m_dispatchResult;

    Ogre::SceneNode*    m_patchRoot;
    Ogre::SceneNode*    m_patchRotate;

    Game*               m_game;
    DataStore*          m_dataStore;
    game::StateGraph    m_dispatcher;

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader    m_StaticPluginLoader;
#endif

protected:
    // components of setup()
    //-------------------------------------------------------------------------
    virtual void createRoot();
    virtual void setupResources();

    /// pure virtual, performs configuration loading and initializes the root
    /// object
    virtual bool configure() = 0;
    virtual void chooseSceneManager();
    virtual void createCamera();
    virtual void createViewports();
    virtual void createResourceListener();
    virtual void loadResources();
    virtual void createScene();
    virtual void createFrameListener();
    virtual void setupDispatcher();

    virtual bool setup();

    // components of teardown()
    //-------------------------------------------------------------------------
    virtual void destroyScene();

    virtual void tearDown();




    // Ogre::FrameListener
    //-------------------------------------------------------------------------
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // Ogre::RenderQueueListener
    //-------------------------------------------------------------------------
    virtual void postRenderQueues();

    // Ogre::WindowEventListener
    //-------------------------------------------------------------------------
    /// Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);

    /// Detach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
};


} // namespace forestrunner

#endif
