#include "BaseApplication.h"

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

class BasicTutorial7 : public BaseApplication
{
public:
    BasicTutorial7(void);
    virtual ~BasicTutorial7(void);

protected:
    CEGUI::OgreRenderer* mRenderer;
    CEGUI::AnimationInstance*   m_anim_flyIn;
    CEGUI::AnimationInstance*   m_anim_flyOut;

    virtual void createScene(void);

    virtual void createFrameListener(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool onAcceptButton(const CEGUI::EventArgs &e);
    bool onRejectButton(const CEGUI::EventArgs &e);
};
