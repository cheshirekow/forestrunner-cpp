#ifndef APPLICATION_H
#define APPLICATION_H

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "gui/GuiManager.h"
#include "game/Game.h"

#include "stategraph/Manager.h"
#include "stategraph/states/Initialize.h"
#include "stategraph/states/Agreement.h"

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


class Application :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public Ogre::RenderQueueListener,
    public OIS::KeyListener,
    public OIS::MouseListener,
    public OIS::MultiTouchListener
{

public:
    Application(void);
    virtual ~Application(void);
    virtual void go();

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

    // OgreBites
    OgreBites::SdkCameraMan*    mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel*     mDetailsPanel;    // sample details panel

    bool mCursorWasVisible;  // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::MultiTouch*    mTouch;
    OIS::Keyboard*      mKeyboard;
    
    //OIS Fake Mouse for touch translation
    OIS::MouseState     mTouchMouseState;

    CEGUI::OgreRenderer*    mRenderer;
    GuiManager*          m_guiManager;

    Ogre::SceneNode*    m_patchRoot;
    Ogre::SceneNode*    m_patchRotate;
    Ogre::Timer*        m_iosTimer;

    Ogre::Overlay*              m_hudOverlay;
    Ogre::OverlayContainer*     m_hudContainer;
    Ogre::TexturePtr            m_hudTex;
    //Ogre::Rectangle2D*          m_miniScreen;
    //Ogre::SceneNode*            m_miniScreenNode;


    stategraph::Manager                 m_stateGraph;
    stategraph::states::Initialize      m_state_01_init;
    stategraph::states::Agreement       m_state_02_agreement;

    Game*               m_game;

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader    m_StaticPluginLoader;
#endif

public:
    // interface for ios
    bool ios_init();
    void ios_cleanup();
    bool ios_step();

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createHUD(void);
    virtual void createCEGUI(void);
    virtual void createScene(void);
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // Ogre::RenderQueueListener
    virtual void postRenderQueues();

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );

    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    // OIS::MultiTouchListener
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
    virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
    virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
    virtual bool touchCancelled( const OIS::MultiTouchEvent &arg );

    // Ogre::WindowEventListener

    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
};


#endif
