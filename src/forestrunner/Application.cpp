#include "Application.h"
#include "MeshBuilder.h"
#include "game/KeyboardGame.h"
#include "game/ForestPatch.h"
#include "game/CEGUIDummyLogger.h"

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





//-------------------------------------------------------------------------------------
Application::Application(void):
    mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mViewport(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCursorWasVisible(false),
    mShutDown(false),
    m_iosTimer(0)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    m_ResourcePath = Ogre::macBundlePath() + "/";
#elif FORESTRUNNER_LINUX
    m_ResourcePath = std::string(g_installPrefix) + "/share/forestrunner/";
#else
#error "Don't know how to complile on this system"
#endif
}




//-------------------------------------------------------------------------------------
Application::~Application(void)
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);

#ifdef OGRE_STATIC_LIB
    m_StaticPluginLoader.unload();
#endif

    delete mRoot;
}




//-------------------------------------------------------------------------------------
bool Application::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        std::cerr << "showConfigDialog() returned true" << std::endl;
        mWindow = mRoot->initialise(true, "Forest Runner");

        return true;
    }
    else
    {
        return false;
    }
}





//-------------------------------------------------------------------------------------
void Application::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mSceneMgr->addRenderQueueListener(this);
}




//-------------------------------------------------------------------------------------
void Application::createScene(void)
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

    m_pLog->logMessage("createScene: creating gui manager");

}




//-------------------------------------------------------------------------------------
void Application::createCamera(void)
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




//-------------------------------------------------------------------------------------
void Application::createFrameListener(void)
{
    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    mRoot->addFrameListener(this);
}




//-------------------------------------------------------------------------------------
void Application::destroyScene(void)
{
}



//-------------------------------------------------------------------------------------
void Application::createViewports(void)
{
    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(1.0,1.0,1.0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(mViewport->getActualWidth()) /
            Ogre::Real(mViewport->getActualHeight()));
}





//-------------------------------------------------------------------------------------
void Application::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(m_ResourcePath + mResourcesCfg);

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
                archName = Ogre::String(m_ResourcePath + archName);
#endif
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}






//-------------------------------------------------------------------------------------
void Application::createResourceListener(void)
{

}






//-------------------------------------------------------------------------------------
void Application::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}



bool Application::ios_init()
{
    mResourcesCfg   = "resources.cfg";
    mPluginsCfg     = "plugins.cfg";

    // instantiate the dummy logger so that it gets set as the singleton
    // for cegui
    CEGUI::DummyLogger* guiLog = new CEGUI::DummyLogger();

    if (!setup())
        return false;

    m_iosTimer = OGRE_NEW Ogre::Timer();
    m_iosTimer->reset();

    mRoot->clearEventTimes();

    return true;
}

void Application::ios_cleanup()
{
    // clean up
    destroyScene();
}


bool Application::ios_step()
{
    /*
    std::cerr << "   viewport: [" 
                << mViewport->getActualLeft() << ", "
                << mViewport->getActualTop() << "] ["
                << mViewport->getActualWidth() << ", "
                << mViewport->getActualHeight() << "]" << std::endl;
    */
    //mRenderer->setDefaultRootRenderTarget(*mWindow);
    Ogre::WindowEventUtilities::messagePump();
    return mRoot->renderOneFrame();
}


//-------------------------------------------------------------------------------------
void Application::go(void)
{
    mResourcesCfg   = "resources.cfg";
    mPluginsCfg     = "plugins.cfg";

    if (!setup())
        return;

    //mRoot->startRendering();

    mRoot->getRenderSystem()->_initRenderTargets();
    mRoot->clearEventTimes();

    while(!mWindow->isClosed() && !mShutDown )
    {
        //Pump messages in all registered RenderWindow windows
        Ogre::WindowEventUtilities::messagePump();
        mRoot->renderOneFrame();
        //CEGUI::System::getSingleton().renderAllGUIContexts();
    }


    // clean up
    destroyScene();
}





//-------------------------------------------------------------------------------------
bool Application::setup(void)
{
    new Ogre::LogManager();

    m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);

    Ogre::String pluginsPath;
    // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
    pluginsPath = m_ResourcePath + mPluginsCfg;
#endif

    mRoot = new Ogre::Root(pluginsPath, m_ResourcePath + "ogre.cfg");

#ifdef OGRE_STATIC_LIB
    m_StaticPluginLoader.load();
#endif

    setupResources();

    m_pLog->logMessage("setup: Finished setting up resources about to show config");

    bool carryOn = configure();
    if (!carryOn) return false;

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

    return true;
}



//-------------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    //return Application::frameRenderingQueued(evt);
    // apparently clears the viewport after its drawn, not before

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;
    
    m_game->update(evt.timeSinceLastFrame);

    // this is how we update the camera controller
    // (probably need to get rid of this)
    // once we fix the camera location

    return true;
}







void Application::postRenderQueues()
{

}








//Adjust mouse clipping area
void Application::windowResized(Ogre::RenderWindow* rw)
{
    if(mCamera && mViewport)
    {
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Ogre::Real(mViewport->getActualWidth()) /
            Ogre::Real(mViewport->getActualHeight()));
    }

}

//Unattach OIS before window shutdown (very important under Linux)
void Application::windowClosed(Ogre::RenderWindow* rw)
{

}



} // namespace forestrunner



