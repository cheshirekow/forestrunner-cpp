#ifndef FORESTRUNNER_APPLICATION_H
#define FORESTRUNNER_APPLICATION_H

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <Ogre.h>


#include "gui/GuiManager.h"
#include "game/Game.h"


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

    bool mCursorWasVisible;  // was cursor visible before dialog appeared
    bool mShutDown;

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

    // Ogre::WindowEventListener

    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
};


} // namespace forestrunner

#endif
