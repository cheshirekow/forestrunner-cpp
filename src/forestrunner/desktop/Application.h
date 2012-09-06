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
 *  along with forestrunner.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   Application.h
 *
 *  \date   Aug 29, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_DESKTOP_APPLICATION_H_
#define FORESTRUNNER_DESKTOP_APPLICATION_H_

#include "forestrunner/Application.h"
#include "game/KeyboardGame.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>

#include "gui/GuiManager.h"



namespace forestrunner {
namespace      desktop {




/// extends application with input handler
class Application:
    public forestrunner::Application,
    public OIS::KeyListener,
    public OIS::MouseListener,
    public OIS::MultiTouchListener
{
    public:
        typedef forestrunner::Application Base_t;

    protected:
        //OIS Input devices
        OIS::InputManager*  mInputManager;
        OIS::Mouse*         mMouse;
        OIS::MultiTouch*    mTouch;
        OIS::Keyboard*      mKeyboard;

        //OIS Fake Mouse for touch translation
        OIS::MouseState     mTouchMouseState;

        //kind of abstracts away the process of dealing with CEGUI
        CEGUI::OgreRenderer*        mRenderer;
        GuiManager*                 m_guiManager;

        Ogre::Overlay*              m_hudOverlay;
        Ogre::OverlayContainer*     m_hudContainer;
        Ogre::TexturePtr            m_hudTex;
        //Ogre::Rectangle2D*          m_miniScreen;
        //Ogre::SceneNode*            m_miniScreenNode;

        KeyboardGame                m_inputHandler;


    public:
        Application(forestrunner::DataStore* dataStore);
        virtual ~Application();
        void go();

    protected:
        // overrides for setup()
        //----------------------------------------------------------------------
        virtual bool configure();
                void createHUD();
                void createCEGUI();
        /// overrides base class to add creation of the gui manager
        virtual void createScene();
        virtual void createFrameListener();
        virtual void setupDispatcher();

        // overrides for teardown()
        //----------------------------------------------------------------------
        virtual void destroyScene();



        // Ogre::FrameListener
        //----------------------------------------------------------------------
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        // Ogre::RenderQueueListener
        //----------------------------------------------------------------------
        virtual void postRenderQueues();

        // Ogre::WindowEventListener
        //----------------------------------------------------------------------
        virtual void windowResized(Ogre::RenderWindow* rw);
        virtual void windowClosed(Ogre::RenderWindow* rw);

        // OIS::KeyListener
        //----------------------------------------------------------------------
        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );

        // OIS::MouseListener
        //----------------------------------------------------------------------
        virtual bool mouseMoved( const OIS::MouseEvent &arg );
        virtual bool mousePressed( const OIS::MouseEvent &arg,
                                        OIS::MouseButtonID id );
        virtual bool mouseReleased( const OIS::MouseEvent &arg,
                                        OIS::MouseButtonID id );

        // OIS::MultiTouchListener
        //----------------------------------------------------------------------
        virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
        virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
        virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
        virtual bool touchCancelled( const OIS::MultiTouchEvent &arg );
};


} // nemspace desktop
} // namespace forestrunner 

#endif // APPLICATION_H_
