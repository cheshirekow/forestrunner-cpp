#include "Application.h"
#include <cassert>
#include <sigc++/sigc++.h>


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

    CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("fly.xml");

    m_guiManager = new GuiManager();
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

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyPressed( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyPressed(arg);

    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(arg.key);
    sys.injectChar(arg.text);
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::keyReleased( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyReleased(arg);

    CEGUI::System::getSingleton().injectKeyUp(arg.key);
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
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return BaseApplication::mousePressed(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return BaseApplication::mouseReleased(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}



//-------------------------------------------------------------------------------------
bool Application::onAcceptButton(const CEGUI::EventArgs &e)
{
    return true;
}




//-------------------------------------------------------------------------------------
bool Application::onRejectButton(const CEGUI::EventArgs &e)
{
    mShutDown = true;
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
