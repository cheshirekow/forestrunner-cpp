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

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/RendererModules/Ogre/ResourceProvider.h>
#include <CEGUI/RendererModules/Ogre/ImageCodec.h>

#include <CEGUI/RendererModules/OpenGL/Renderer.h>

#define CEGUI_RTT 1
//#define CEGUI_GL 1

#ifdef CEGUI_GL
#include <CEGUI/RendererModules/OpenGL/Renderer.h>
#endif





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
    mKeyboard(0),
    m_guiManager(0)
{

}

DesktopApplication::~DesktopApplication()
{
}


//------------------------------------------------------------------------------
void DesktopApplication::go(void)
{
    if (!setup())
        return;

    //mRoot->startRendering();

    mRoot->getRenderSystem()->_initRenderTargets();
    mRoot->clearEventTimes();

    while(!mWindow->isClosed() && !mShutDown )
        mShutDown = !step();

    // clean up
    tearDown();
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




//------------------------------------------------------------------------------
bool DesktopApplication::configure()
{
    m_pLog->logMessage(
            "setup: Finished setting up resources about to show config");

    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window
        // by passing 'true'
        std::cerr << "showConfigDialog() returned true" << std::endl;
        mWindow = mRoot->initialise(true, "Forest Runner");

        return true;
    }
    else
    {
        return false;
    }
}




void DesktopApplication::createHUD(void)
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
    //m_hudOverlay->hide();
}



void DesktopApplication::createCEGUI(void)
{
    m_pLog->logMessage("createScene: About to bootstrap cegui");

#ifdef CEGUI_RTT
        CEGUI::Renderer* renderer;
#    ifdef CEGUI_GL
            renderer = &CEGUI::OpenGLRenderer::create();
#   else
            mRenderer = &CEGUI::OgreRenderer::create(*m_hudTex->getBuffer()->getRenderTarget());
            mRenderer->setFrameControlExecutionEnabled(false);
            renderer = mRenderer;
#   endif
        CEGUI::OgreResourceProvider& rp = CEGUI::OgreRenderer::createOgreResourceProvider();
        CEGUI::OgreImageCodec& ic       = CEGUI::OgreRenderer::createOgreImageCodec();
        CEGUI::System::create(
                *renderer,
                static_cast<CEGUI::ResourceProvider*>(&rp),
                static_cast<CEGUI::XMLParser*>(0),
                static_cast<CEGUI::ImageCodec*>(&ic) );
#else
        CEGUI::Renderer* renderer;
        if(CEGUI_GL)
            renderer = &CEGUI::OpenGLRenderer::create();
        else
        {
            mRenderer = &CEGUI::OgreRenderer::create();
            renderer = mRenderer;
        }
        CEGUI::OgreResourceProvider& rp = CEGUI::OgreRenderer::createOgreResourceProvider();
        CEGUI::OgreImageCodec& ic       = CEGUI::OgreRenderer::createOgreImageCodec();
        CEGUI::System::create(
                *renderer,
                &rp,
                static_cast<CEGUI::XMLParser*>(0),
                &ic );
#endif

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

    //CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    m_pLog->logMessage("createScene: loading animations");

    CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("ForestRunner.xml");
}





//-------------------------------------------------------------------------------------
void DesktopApplication::createScene(void)
{
    //call base class scene creation
    Application::createScene();

    // initialize CEGUI
    createHUD();
    createCEGUI();

    m_guiManager = new GuiManager(m_game);
}


bool DesktopApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(!Application::frameRenderingQueued(evt))
        return false;


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

    // update cegui
        //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(evt.timeSinceLastFrame);


#ifdef CEGUI_RTT
#ifndef CEGUI_GL
    Ogre::RenderTexture *renderTexture =
        m_hudTex->getBuffer()->getRenderTarget();
    renderTexture->getViewport(0)->clear(
            Ogre::FBT_COLOUR| Ogre::FBT_DEPTH,
            Ogre::ColourValue::ZERO,
            0.0);
    CEGUI::System::getSingleton().renderAllGUIContexts();
#endif
#endif

    return true;
}


void DesktopApplication::postRenderQueues()
{
#ifdef  CEGUI_GL
    std::cerr << "all render queues processed, rendering gui" << std::endl;
    CEGUI::System::getSingleton().renderAllGUIContexts();
#endif
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
