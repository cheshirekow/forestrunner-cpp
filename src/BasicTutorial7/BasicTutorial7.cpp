#include "BasicTutorial7.h"
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
BasicTutorial7::BasicTutorial7(void)
{
}




//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
}




//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
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

    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *guiRoot      = wmgr.loadWindowLayout("agreement.layout");
    CEGUI::System::getSingleton().setGUISheet(guiRoot);

    CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("fly.xml");

    m_anim_flyIn =
        CEGUI::AnimationManager::getSingleton().instantiateAnimation("FlyIn");
    // after we instantiate the animation, we have to set its target window
    m_anim_flyIn->setTargetWindow(guiRoot);
    // at this point, you can start this instance and see the results
    m_anim_flyIn->start();

    m_anim_flyOut =
        CEGUI::AnimationManager::getSingleton().instantiateAnimation("FlyOut");
    // after we instantiate the animation, we have to set its target window
    m_anim_flyOut->setTargetWindow(guiRoot);



    CEGUI::Window* btn;
    btn = guiRoot->getChildRecursive(
                        "RootWindow/FrameWindow/AcceptButton");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &BasicTutorial7::onAcceptButton,
                                this) );

    btn = guiRoot->getChildRecursive(
                        "RootWindow/FrameWindow/RejectButton");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &BasicTutorial7::onRejectButton,
                                this) );
}




//-------------------------------------------------------------------------------------
void BasicTutorial7::createFrameListener(void)
{
    //BaseApplication::createFrameListener();

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

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
bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
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
bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyPressed(arg);

    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(arg.key);
    sys.injectChar(arg.text);
    return true;
}




//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
    //return BaseApplication::keyReleased(arg);

    CEGUI::System::getSingleton().injectKeyUp(arg.key);
    return true;
}




//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
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
bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return BaseApplication::mousePressed(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true;
}




//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return BaseApplication::mouseReleased(arg, id);

    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}



//-------------------------------------------------------------------------------------
bool BasicTutorial7::onAcceptButton(const CEGUI::EventArgs &e)
{
    m_anim_flyOut->start();
    return true;
}




//-------------------------------------------------------------------------------------
bool BasicTutorial7::onRejectButton(const CEGUI::EventArgs &e)
{
    mShutDown = true;
    return true;
}





int main(int argc, char *argv[])
{
    // Create application object
    BasicTutorial7 app;

    try
    {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
