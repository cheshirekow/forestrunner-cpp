#include "Application.h"
#include "MeshBuilder.h"
#include "game/KeyboardGame.h"

#include <cassert>
#include <cmath>
#include <sigc++/sigc++.h>

#include <OGRE/SdkTrays.h>
#include <OgreMath.h>

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
Application::Application(void)
{

}




//-------------------------------------------------------------------------------------
Application::~Application(void)
{

}




//-------------------------------------------------------------------------------------
void Application::createScene(void)
{
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::AnimationManager::setDefaultResourceGroup("Animations");

    CEGUI::SchemeManager::getSingleton().create("GlossySerpent.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

    CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("ForestRunner.xml");

    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

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

    float sideLen   = 5.0f;
    int   numX      = 40;
    int   numY      = 30;
    meshbuilder::create_grid(mSceneMgr,"ForestRunnerGrid",sideLen,numX,numY);
    Ogre::Entity* grid =
            mSceneMgr->createEntity("grid", "ForestRunnerGrid");
    grid->setMaterialName("ForestRunner/BlackWireframe");

    Ogre::SceneNode* gridNode =
        m_patchRoot->createChildSceneNode("GridNode");
    gridNode->translate(-(numX*sideLen)/2.0f,0,2*sideLen);

    gridNode->attachObject(grid);

    m_game = new KeyboardGame();
    m_game->m_patchRoot     = m_patchRoot;
    m_game->m_patchRotate   = m_patchRotate;

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
    mCamera->setFarClipDistance(1000);

    //mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}




//-------------------------------------------------------------------------------------
void Application::createFrameListener(void)
{
    //BaseApplication::createFrameListener();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));


    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(
                mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(
                mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}




//-------------------------------------------------------------------------------------
void Application::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(1.0,1.0,1.0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}




//-------------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    //return BaseApplication::frameRenderingQueued(evt);

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    m_game->update(evt.timeSinceLastFrame);

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    // this is how we update the camera controller
    // (probably need to get rid of this)
    // once we fix the camera location
    //mCameraMan->frameRenderingQueued(evt);

    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyPressed( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyReleased(arg);

    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(arg.key);
    sys.injectChar(arg.text);
    m_game->keyPressed(arg);

    //mCameraMan->injectKeyDown(arg);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyReleased( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyReleased(arg);

    CEGUI::System::getSingleton().injectKeyUp(arg.key);
    m_game->keyReleased(arg);
    //mCameraMan->injectKeyUp(arg);

    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mouseMoved( const OIS::MouseEvent &arg )
{
    //return BaseApplication::mouseMoved(arg);

    CEGUI::System &sys = CEGUI::System::getSingleton();
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
    //return BaseApplication::mousePressed(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    //mCameraMan->injectMouseDown(arg,id);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return BaseApplication::mouseReleased(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    //mCameraMan->injectMouseUp(arg,id);
    return true;
}





int main(int argc, char *argv[])
{
    // Create application object
    Application app;

    try
    {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
