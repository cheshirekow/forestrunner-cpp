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

#include "Application.h"
#include "MeshBuilder.h"
#include "game/KeyboardGame.h"
#include "game/ForestPatch.h"

#ifdef FORESTRUNNER_LINUX
#include "app/linux.h"
#endif


#include <cassert>
#include <cmath>
#include <sigc++/sigc++.h>

#include <OgreMath.h>






#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    #include <iOS/macUtils.h>
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    #include <iOS/macUtils.h>
#endif


namespace forestrunner {




//------------------------------------------------------------------------------
Application::Application(DataStore* store):
    mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mViewport(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCursorWasVisible(false),
    mShutDown(false),
    m_dataStore(store)
{
#if FORESTRUNNER_OSX
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources";
#elif FORESTRUNNER_IOS
    m_ResourcePath = Ogre::macBundlePath() + "/resources";
#elif FORESTRUNNER_LINUX
    m_ResourcePath = std::string(g_installPrefix) + "/share/forestrunner";
#else
#error "Don't know how to complile on this system"
#endif
}




//------------------------------------------------------------------------------
Application::~Application()
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);

#ifdef OGRE_STATIC_LIB
    m_StaticPluginLoader.unload();
#endif

    delete mRoot;
}









bool Application::step()
{
    /*
    std::cerr << "   viewport: ["
                << mViewport->getActualLeft() << ", "
                << mViewport->getActualTop() << "] ["
                << mViewport->getActualWidth() << ", "
                << mViewport->getActualHeight() << "]" << std::endl;
    */
    //mRenderer->setDefaultRootRenderTarget(*mWindow);

    //Pump messages in all registered RenderWindow windows
    Ogre::WindowEventUtilities::messagePump();

    return mRoot->renderOneFrame();
}




void Application::createRoot()
{
    
    new Ogre::LogManager();

    m_pLog = Ogre::LogManager::getSingleton()
                    .createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);

    m_pLog->logMessage("Ogre Log Initialized");

    Ogre::String pluginsPath;
        // only use plugins.cfg if not static
    #ifndef OGRE_STATIC_LIB
        pluginsPath = m_ResourcePath + "/" + mPluginsCfg;
    #endif

    m_pLog->logMessage("setup(): creating root");
    mRoot = new Ogre::Root(pluginsPath, m_ResourcePath + "/ogre.cfg");

    m_pLog->logMessage("setup(): loading plugins");
    #ifdef OGRE_STATIC_LIB
        m_StaticPluginLoader.load();
    #endif
}




//------------------------------------------------------------------------------
void Application::setupResources()
{
    std::cout << "setup() : Setting up resources" << std::endl;

    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(m_ResourcePath + "/" + mResourcesCfg);
    
    std::cout << "setup() : loaded resource config file" << std::endl;

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
                archName = Ogre::String(m_ResourcePath + "/" + archName);
#endif
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}




//------------------------------------------------------------------------------
void Application::chooseSceneManager()
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mSceneMgr->addRenderQueueListener(this);
}




//------------------------------------------------------------------------------
void Application::createCamera()
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,10,20));

    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-10));
    mCamera->setNearClipDistance(1);
    mCamera->setFarClipDistance(180);

}




//------------------------------------------------------------------------------
void Application::createViewports()
{
    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(1.0,1.0,1.0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(mViewport->getActualWidth()) /
            Ogre::Real(mViewport->getActualHeight()));
}




//------------------------------------------------------------------------------
void Application::createResourceListener()
{

}




//------------------------------------------------------------------------------
void Application::loadResources()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}




//------------------------------------------------------------------------------
void Application::createScene()
{

    m_pLog->logMessage("createScene: loading aircraft");

    // Create an Entity
    //Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::Entity* aircraft =
        mSceneMgr->createEntity("aircraft", "aircraft.mesh","General");

    aircraft->setMaterialName("ForestRunner/Gray");

    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* acNode =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("AircraftNode");

    acNode->attachObject(aircraft);

    Ogre::Entity* aircraftWF =
        mSceneMgr->createEntity("aircraftWF", "aircraft.mesh","General");

    aircraftWF->setMaterialName("ForestRunner/BlackWireframe");

    Ogre::SceneNode* acwfNode =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("AircraftWFNode");

    acwfNode->attachObject(aircraftWF);
    acwfNode->scale(1.05,1.05,1.05);

    Ogre::Entity* aircraftOL =
        mSceneMgr->createEntity("aircraftOL", "aircraft_outline.mesh","General");

    aircraftOL->setMaterialName("ForestRunner/Black");

    Ogre::SceneNode* acolNode =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("AircraftOLNode");

    acolNode->attachObject(aircraftOL);
    acolNode->scale(1.2,1.2,1.2);

    m_patchRotate =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("patchRotate");
    m_patchRoot = m_patchRotate->createChildSceneNode("patchRoot");

    m_pLog->logMessage("createScene: creating crid");

    float sideLen   = 5.0f;
    int   numX      = 40;
    int   numY      = 40;
    meshbuilder::create_grid(mSceneMgr,"ForestRunnerGrid",sideLen,numX,numY);
    Ogre::Entity* grid =
            mSceneMgr->createEntity("grid", "ForestRunnerGrid");
    grid->setMaterialName("ForestRunner/BlackWireframe");

    Ogre::SceneNode* gridNode =
        m_patchRoot->createChildSceneNode("GridNode");
    gridNode->translate(-(numX*sideLen)/2.0f,0,2*sideLen);

    gridNode->attachObject(grid);

    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));



    m_pLog->logMessage("createScene: creating game");

    m_game = new KeyboardGame();
    m_game->createScene(mSceneMgr,m_patchRoot,m_patchRotate);

    m_dataStore->sig_valueChanged.connect(
            sigc::mem_fun(*m_game,&Game::valueChanged) );
}




//------------------------------------------------------------------------------
void Application::createFrameListener()
{
    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    mRoot->addFrameListener(this);
}




//------------------------------------------------------------------------------
void Application::setupDispatcher()
{
    m_dispatcher.initCycle.setNumPatches(m_game->getNumPatches());

    m_dispatcher.sig_initRun.connect(
                sigc::mem_fun(*m_game,&Game::initRun) );

    m_dispatcher.sig_stepRun.connect(
                sigc::mem_fun(*m_game,&Game::update_game) );

    m_game->sig_crashed.connect(
                sigc::mem_fun(m_dispatcher,&game::StateGraph::crash));

    m_game->sig_paused.connect(
                sigc::mem_fun(m_dispatcher,&game::StateGraph::pause));

    m_dispatcher.initCycle.sig_clearPatch.connect(
                sigc::mem_fun(*m_game,&Game::clearPatch) );

    m_dispatcher.initCycle.sig_freeMeshes.connect(
                sigc::mem_fun(*m_game,&Game::destroyCylinderMeshes) );

    m_dispatcher.initCycle.sig_createMeshes.connect(
                sigc::mem_fun(*m_game,&Game::createCylinderMeshes) );

    m_dispatcher.initCycle.sig_initPatch.connect(
                sigc::mem_fun(*m_game,&Game::initPatch) );

    m_dispatcher.sig_setLighting.connect(
                sigc::mem_fun(*m_game,&Game::setLighting) );

}




//------------------------------------------------------------------------------
bool Application::setup()
{
#ifdef FORESTRUNNER_IOS
    mResourcesCfg   = "config/ios/resources.cfg";
    mPluginsCfg     = "config/ios/plugins.cfg";

#else
    mResourcesCfg   = "resources.cfg";
    mPluginsCfg     = "plugins.cfg";
#endif

    createRoot();
    setupResources();

    if(!configure()) return false;
    m_pLog->logMessage("setup: Finished showing config");
   
    chooseSceneManager();
    m_pLog->logMessage("setup: Finished setting up scene manager");

    createCamera();
    m_pLog->logMessage("setup: Finished setting up camera");

    createViewports();
    m_pLog->logMessage("setup: Finished setting up viewports");

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    m_pLog->logMessage("setup: Finished setting default mip maps");

    // Create any resource listeners (for loading screens)
    createResourceListener();
    m_pLog->logMessage("setup: Finished setting up resource listeners");

    // Load resources
    loadResources();
    m_pLog->logMessage("setup: Finished loading resources");

    // Create the scene
    createScene();
    m_pLog->logMessage("setup: Finished creating the scene");

    createFrameListener();
    m_pLog->logMessage("setup: Finished creating frame listener, returning");

    setupDispatcher();
    m_pLog->logMessage("setup: Finished setting up dispatcher");

    return true;
}




//------------------------------------------------------------------------------
void Application::destroyScene()
{
}




//------------------------------------------------------------------------------
void Application::tearDown()
{
    destroyScene();
}




//------------------------------------------------------------------------------
//                    Ogre::FrameListener
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    //return Application::frameRenderingQueued(evt);
    // apparently clears the viewport after its drawn, not before

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;
    
    m_dispatcher.step(evt.timeSinceLastFrame);

    // this is how we update the camera controller
    // (probably need to get rid of this)
    // once we fix the camera location

    return true;
}




//------------------------------------------------------------------------------
//                    Ogre::RenderQueueListener
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void Application::postRenderQueues()
{

}




//------------------------------------------------------------------------------
//                    Ogre::WindowEventListener
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void Application::windowResized(Ogre::RenderWindow* rw)
{
    //Adjust mouse clipping area
    if(mCamera && mViewport)
    {
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Ogre::Real(mViewport->getActualWidth()) /
            Ogre::Real(mViewport->getActualHeight()));
    }

}




//------------------------------------------------------------------------------
void Application::windowClosed(Ogre::RenderWindow* rw)
{

}




} // namespace forestrunner



