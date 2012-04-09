#ifndef APPLICATION_H
#define APPLICATION_H

#include "BaseApplication.h"

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "gui/GuiManager.h"
#include "game/Game.h"

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

class Application :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
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
    Ogre::String            mResourcesCfg;
    Ogre::String            mPluginsCfg;

    // OgreBites
    OgreBites::SdkCameraMan*    mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel*     mDetailsPanel;    // sample details panel

    bool mCursorWasVisible;  // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    CEGUI::OgreRenderer* mRenderer;
    GuiManager*          m_guiManager;

    Ogre::SceneNode*    m_patchRoot;
    Ogre::SceneNode*    m_patchRotate;

    Game*               m_game;

    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void);
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);


    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

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
