#ifndef FORESTRUNNER_APPLICATION_H
#define FORESTRUNNER_APPLICATION_H

#include <Ogre.h>

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
    /// does nothing but initialize pointers to null and assigns the value of
    /// the resource path
    Application(void);

    /// cleans up the window listener interface
    virtual ~Application(void);

    /// performs setup(), then enters render loop
    virtual void go();

    /// prcesses the message queue, then renders one frame
    virtual bool step();

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

    Ogre::SceneNode*    m_patchRoot;
    Ogre::SceneNode*    m_patchRotate;
    Ogre::Timer*        m_iosTimer;

    Game*               m_game;

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader    m_StaticPluginLoader;
#endif

protected:
    // components of setup()
    //-------------------------------------------------------------------------
    virtual void createRoot(void);
    virtual void setupResources(void);
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual void createScene(void);
    virtual void createFrameListener(void);

    virtual bool setup();

    // components of teardown()
    //-------------------------------------------------------------------------
    virtual void destroyScene(void);

    virtual void tearDown(void);




    // Ogre::FrameListener
    //-------------------------------------------------------------------------
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // Ogre::RenderQueueListener
    //-------------------------------------------------------------------------
    virtual void postRenderQueues();

    // Ogre::WindowEventListener
    //-------------------------------------------------------------------------
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
};


} // namespace forestrunner

#endif
