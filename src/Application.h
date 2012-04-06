#include "BaseApplication.h"

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "gui/GuiManager.h"
#include "game/Game.h"

class Application :
    public BaseApplication
{

public:
    Application(void);
    virtual ~Application(void);

protected:
    CEGUI::OgreRenderer* mRenderer;
    GuiManager*          m_guiManager;

    Ogre::SceneNode*    m_patchRoot;
    Ogre::SceneNode*    m_patchRotate;

    Game*               m_game;

    virtual void createScene(void);

    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createViewports(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

};
