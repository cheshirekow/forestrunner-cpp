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
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   Application.cpp
 *
 *  \date   Aug 29, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/DesktopApplication.h"

namespace forestrunner {


static CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
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




DesktopApplication::DesktopApplication():
    mInputManager(0),
    mMouse(0),
    mTouch(0),
    mKeyboard(0)
{

}

DesktopApplication::~DesktopApplication()
{
}


void DesktopApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));


#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) || OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32

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

    // call this after we setup OIS so that we get the callback below
    Application::createFrameListener();
}

bool DesktopApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // Fixme: move this stuff back into parent class
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

    return Application::frameRenderingQueued(evt);
}








//-------------------------------------------------------------------------------------
bool DesktopApplication::keyPressed( const OIS::KeyEvent &arg )
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
bool DesktopApplication::keyReleased( const OIS::KeyEvent &arg )
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
bool DesktopApplication::mouseMoved( const OIS::MouseEvent &arg )
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
bool DesktopApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return Application::mousePressed(arg, id);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseButtonDown(convertButton(id));
    //mCameraMan->injectMouseDown(arg,id);
    return true;
}




//-------------------------------------------------------------------------------------
bool DesktopApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //return Application::mouseReleased(arg, id);

    CEGUI::GUIContext& sys =
            CEGUI::System::getSingleton().getDefaultGUIContext();
    sys.injectMouseButtonUp(convertButton(id));
    //mCameraMan->injectMouseUp(arg,id);
    return true;
}



bool DesktopApplication::touchMoved( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.X = arg.state.X;
    mTouchMouseState.Y = arg.state.Y;

    OIS::MouseEvent evt(0,mTouchMouseState);
    mouseMoved(evt );
    return true;
}


bool DesktopApplication::touchPressed( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.buttons = 0x01;
    mTouchMouseState.X       = arg.state.X;
    mTouchMouseState.Y       = arg.state.Y;

    OIS::MouseEvent evt(0,mTouchMouseState);
    mousePressed(evt, OIS::MB_Left);
    return true;
}



bool DesktopApplication::touchReleased( const OIS::MultiTouchEvent &arg )
{
    mTouchMouseState.buttons = 0x0;
    mTouchMouseState.X       = arg.state.X;
    mTouchMouseState.Y       = arg.state.Y;

    OIS::MouseEvent evt(0,mTouchMouseState);
    mouseReleased(evt, OIS::MB_Left);
    return true;
}



bool DesktopApplication::touchCancelled( const OIS::MultiTouchEvent &arg )
{
    return true;
}




//Adjust mouse clipping area
void DesktopApplication::windowResized(Ogre::RenderWindow* rw)
{
    Application::windowResized(rw);
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

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
void DesktopApplication::windowClosed(Ogre::RenderWindow* rw)
{
    Application::windowClosed(rw);
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



} // namespace forestrunner 
