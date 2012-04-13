#include "Application.h"
#include "MeshBuilder.h"
#include "game/KeyboardGame.h"
#include "game/ForestPatch.h"
#include "game/CEGUIDummyLogger.h"

#include <cassert>
#include <cmath>
#include <sigc++/sigc++.h>

#include <OgreMath.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    #include <iPhone/macUtils.h>
#elif defined(OGRE_IS_IOS)
    #include <iPhone/macUtils.h>
#endif

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}


//-------------------------------------------------------------------------------------
Application::Application(void):
    mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mViewport(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mTouch(0),
    mKeyboard(0),
    m_iosTimer(0)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#elif defined(OGRE_IS_IOS)
    m_ResourcePath = Ogre::macBundlePath() + "/";
#else
    m_ResourcePath = "${CMAKE_INSTALL_PREFIX}/share/forestrunner/";
#endif
}




//-------------------------------------------------------------------------------------
Application::~Application(void)
{
    if (mCameraMan) delete mCameraMan;

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
}


void Application::createHUD(void)
{
    // create texture
    m_hudTex = Ogre::TextureManager::getSingleton().createManual(
                    "hudTex",
                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                    Ogre::TEX_TYPE_2D,
                    mWindow->getWidth(),
                    mWindow->getHeight(),
                    0,
                    Ogre::PF_R8G8B8A8,
                    Ogre::TU_RENDERTARGET);

    Ogre::RenderTexture *renderTexture =
            m_hudTex->getBuffer()->getRenderTarget();

    renderTexture->addViewport(0);
    renderTexture->getViewport(0)->setClearEveryFrame(true);
    renderTexture->getViewport(0)->setBackgroundColour(
                                    Ogre::ColourValue(1.0f,1.0f,1.0f,0.0f));
    renderTexture->getViewport(0)->setOverlaysEnabled(false);
    //renderTexture->setAutoUpdated(true);

    // create billboard and scene nodes


    //implement a miniscreen
    /*
    m_miniScreen = new Ogre::Rectangle2D(true);
    m_miniScreen->setCorners(0.5, -0.5, 1.0, -1.0);
    m_miniScreen->setBoundingBox(
            Ogre::AxisAlignedBox(-100000.0 * Ogre::Vector3::UNIT_SCALE,
                                    100000.0 * Ogre::Vector3::UNIT_SCALE));
    m_miniScreenNode =
            mSceneMgr->getRootSceneNode()->createChildSceneNode("MiniScreenNode");
    m_miniScreenNode->attachObject(m_miniScreen);
    */

    // create material
    Ogre::MaterialPtr renderMaterial =
            Ogre::MaterialManager::getSingleton().create(
                    "hudMat",
                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::Technique* matTechnique = renderMaterial->createTechnique();
    matTechnique->createPass();
    renderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    renderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("hudTex");
    renderMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    //m_miniScreen->setMaterial("hudMat");

    // create an overlay
    m_hudContainer = static_cast<Ogre::OverlayContainer*>(
            Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel","HudOverlayPanel"));

    m_hudContainer->setMetricsMode(Ogre::GMM_PIXELS);
    m_hudContainer->setPosition(0, 0);
    m_hudContainer->setDimensions(  mWindow->getWidth(),
                                    mWindow->getHeight() );
    // Give overlay a texture
    m_hudContainer->setMaterialName("hudMat");


    m_hudOverlay = Ogre::OverlayManager::getSingleton().create("HUD");
    m_hudOverlay->add2D(m_hudContainer);
    m_hudOverlay->show();
}



void Application::createCEGUI(void)
{
    m_pLog->logMessage("createScene: About to bootstrap cegui");
    try
    {
        mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
        //mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(
        //                    *m_hudTex->getBuffer()->getRenderTarget() );
        //mRenderer->setFrameControlExecutionEnabled(false);
    }
    catch( const CEGUI::Exception& e )
    {
        m_pLog->logMessage(Ogre::String("Exception thrown while boostrapping CEGUI: ") + e.what() );
        throw e;
    }

    m_pLog->logMessage("createScene: setting cegui defaults");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::AnimationManager::setDefaultResourceGroup("Animations");

    m_pLog->logMessage("createScene: creating schemes");

    CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpent.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    m_pLog->logMessage("createScene: setting default font and mouse");

    CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );
    //CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

    m_pLog->logMessage("createScene: loading animations");

    CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("ForestRunner.xml");
}





//-------------------------------------------------------------------------------------
void Application::createScene(void)
{

    m_pLog->logMessage("createScene: loading aircraft");

    // Create an Entity
    //Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::Entity* aircraft =
        mSceneMgr->createEntity("aircraft", "aircraft.mesh");

    aircraft->setMaterialName("ForestRunner/Gray");

    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* acNode =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("AircraftNode");

    acNode->attachObject(aircraft);

    Ogre::Entity* aircraftWF =
        mSceneMgr->createEntity("aircraftWF", "aircraft.mesh");

    aircraftWF->setMaterialName("ForestRunner/BlackWireframe");

    Ogre::SceneNode* acwfNode =
        mSceneMgr->getRootSceneNode()->createChildSceneNode("AircraftWFNode");

    acwfNode->attachObject(aircraftWF);
    acwfNode->scale(1.05,1.05,1.05);

    Ogre::Entity* aircraftOL =
        mSceneMgr->createEntity("aircraftOL", "aircraft_outline.mesh");

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

    // initialize CEGUI
    createHUD();
    createCEGUI();

    m_pLog->logMessage("createScene: creating game");

    m_game = new KeyboardGame();
    m_game->createScene(mSceneMgr,m_patchRoot,m_patchRotate);

    m_pLog->logMessage("createScene: creating gui manager");

    m_guiManager = new GuiManager(m_game);

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

    //mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}




//-------------------------------------------------------------------------------------
void Application::createFrameListener(void)
{
    //Application::createFrameListener();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));


#if defined(OGRE_IS_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) || OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32

#else
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif


    mInputManager = OIS::InputManager::createInputSystem( pl );


#ifdef OGRE_IS_IOS
    mTouch = static_cast<OIS::MultiTouch*>(
                mInputManager->createInputObject(OIS::OISMultiTouch, true));
    mTouch->setEventCallback(this);
#else
    mKeyboard = static_cast<OIS::Keyboard*>(
                mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mKeyboard->setEventCallback(this);

    mMouse = static_cast<OIS::Mouse*>(
                mInputManager->createInputObject( OIS::OISMouse, true ));
    mMouse->setEventCallback(this);
#endif

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
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || defined(OGRE_IS_IOS)
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

#ifdef OGRE_IS_IOS
    m_iosTimer = OGRE_NEW Ogre::Timer();
    m_iosTimer->reset();
#endif

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
    std::cerr << "Application::ios_step : here" << std::endl;
    /*
    std::cerr << "   viewport: [" 
                << mViewport->getActualLeft() << ", "
                << mViewport->getActualTop() << "] ["
                << mViewport->getActualWidth() << ", "
                << mViewport->getActualHeight() << "]" << std::endl;
    */
    //mRenderer->setDefaultRootRenderTarget(*mWindow);
    return mRoot->renderOneFrame();
}


//-------------------------------------------------------------------------------------
void Application::go(void)
{
    mResourcesCfg   = "resources.cfg";
    mPluginsCfg     = "plugins.cfg";

    if (!setup())
        return;

    mRoot->startRendering();

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
};



//-------------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    //return Application::frameRenderingQueued(evt);

    // apparently clears the viewport after its drawn, not before
    /*
    Ogre::RenderTexture *renderTexture =
            m_hudTex->getBuffer()->getRenderTarget();
    renderTexture->getViewport(0)->clear(
            Ogre::FBT_COLOUR| Ogre::FBT_DEPTH,
            Ogre::ColourValue::ZERO,
            0.0);

    CEGUI::System::getSingleton().renderAllGUIContexts();
    */

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;
    
    //Need to capture/update each device
    if(mKeyboard)
        mKeyboard->capture();
    if(mMouse)
        mMouse->capture();
    if(mTouch)
        mTouch->capture();

    m_game->update(evt.timeSinceLastFrame);

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(evt.timeSinceLastFrame);

    // this is how we update the camera controller
    // (probably need to get rid of this)
    // once we fix the camera location
    //mCameraMan->frameRenderingQueued(evt);

    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyPressed( const OIS::KeyEvent &arg )
{
    //return Application::keyReleased(arg);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectKeyDown( (CEGUI::Key::Scan)arg.key );
    sys.injectChar(arg.text);
    m_game->keyPressed(arg);

    //mCameraMan->injectKeyDown(arg);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyReleased( const OIS::KeyEvent &arg )
{
    //return Application::keyReleased(arg);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectKeyUp( (CEGUI::Key::Scan)arg.key );
    m_game->keyReleased(arg);
    //mCameraMan->injectKeyUp(arg);

    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mouseMoved( const OIS::MouseEvent &arg )
{
    //return Application::mouseMoved(arg);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
        sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
    //mCameraMan->injectMouseMove(arg);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return Application::mousePressed(arg, id);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseButtonDown(convertButton(id));
    //mCameraMan->injectMouseDown(arg,id);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return Application::mouseReleased(arg, id);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseButtonUp(convertButton(id));
    //mCameraMan->injectMouseUp(arg,id);
    return true;
}



bool Application::touchMoved( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.X = arg.state.X;
    mTouchMouseState.Y = arg.state.Y;
    
    OIS::MouseEvent evt(0,mTouchMouseState);
    mouseMoved(evt );
    return true;
}


bool Application::touchPressed( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.buttons = 0x01;
    mTouchMouseState.X       = arg.state.X;
    mTouchMouseState.Y       = arg.state.Y;
    
    OIS::MouseEvent evt(0,mTouchMouseState);
    mousePressed(evt, OIS::MB_Left);
    return true;
}



bool Application::touchReleased( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.buttons = 0x0;
    mTouchMouseState.X       = arg.state.X;
    mTouchMouseState.Y       = arg.state.Y;
    
    OIS::MouseEvent evt(0,mTouchMouseState);
    mouseReleased(evt, OIS::MB_Left);
    return true;
}



bool Application::touchCancelled( const OIS::MultiTouchEvent &arg )
{
    return true;
}




//Adjust mouse clipping area
void Application::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
    
    if(mCamera && mViewport)
    {
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Ogre::Real(mViewport->getActualWidth()) /
            Ogre::Real(mViewport->getActualHeight()));
    }

    if(mMouse)
    {
        const OIS::MouseState &ms = mMouse->getMouseState();
        ms.width = width;
        ms.height = height;
    }
    
    mTouchMouseState.width   = width;
    mTouchMouseState.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void Application::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            if(mMouse)
                mInputManager->destroyInputObject( mMouse );
            if(mKeyboard)
                mInputManager->destroyInputObject( mKeyboard );
            if(mTouch)
                mInputManager->destroyInputObject( mTouch );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}







