/*
 *  \file   Game.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef GAME_H_
#define GAME_H_

#include <OgreMath.h>
#include <OgreMesh.h>
#include <OISKeyboard.h>
#include <sigc++/sigc++.h>

#include "GameState.h"
#include "InitCycle.h"
#include "ForestPatch.h"
#include "game/StateGraph.h"

class Game
{
    protected:
        GameState   m_gameState;

        float   m_density;
        float   m_xAccel;
        float   m_xSpeedMax;
        float   m_xSpeed;
        float   m_ySpeed;

        float   m_radius;
        float   m_height;
        float   m_outline;

        float   m_xPos;
        float   m_yPos;
        float   m_patchWidth;
        float   m_patchHeight;
        float   m_acSide;
        float   m_acRadius;
        float   m_acTrans;
        float   m_score;
        int     m_patchDimX;
        int     m_patchDimY;

        InitCycle   m_init;
        forestrunner::game::StateGraph  m_dispatcher;

        ForestPatch** m_patches;
        std::vector<Ogre::MaterialPtr>  m_materials;
        std::vector<Ogre::Entity*>      m_coloredEntities;

        sigc::signal<void,GameState> m_sig_stateChanged;
        sigc::signal<void,float>    m_sig_scoreChanged;
        sigc::signal<void,float>    m_sig_progressChanged;

        Ogre::SceneNode*    m_patchRoot;
        Ogre::SceneNode*    m_patchRotate;
        Ogre::SceneManager* m_sceneMgr;

        Ogre::MeshPtr       m_cylinderMesh;
        Ogre::MeshPtr       m_cylinderFrame;
        Ogre::MeshPtr       m_cylinderOutline;

        Ogre::Entity*       m_cylinderFrameEntity;
        Ogre::Entity*       m_cylinderOutlineEntity;


    public:
        sigc::signal<void,float>    sig_score;
        sigc::signal<void>          sig_crashed;

        Game();
        virtual ~Game();

        /// removes all the cylinder meshes and their associated 'entities'
        /// from the scene
        void destroyCylinderMeshes();

        /// creates cylinder meshes and generates 'entities' (instances) for
        /// the cylinders
        void createCylinderMeshes();

        /// clears the i'th patch
        void clearPatch(int i);

        /// initializes the i'th patch
        void initPatch(int i);

        /// resets the init loop
        void initFinished();

        /// simply emits a progress signal
        void initProgress(float progress);

        /// set the game speed
        void setSpeed(int i);

        /// set the game density
        void setDensity(int i);

        /// set the game radius
        void setRadius(int i);

        /// initialize a new run of the game
        void initRun();



        void createScene(Ogre::SceneManager* sceneMgr,
                            Ogre::SceneNode* patchRoot,
                            Ogre::SceneNode* patchRotate);

        GameState getState();
        void setState(GameState state);

        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );

        void update_game( Ogre::Real tpf );
        virtual void update( Ogre::Real tpf );
        virtual void updateSpeed( Ogre::Real tpf )=0;

        sigc::signal<void,GameState>& sig_stateChanged();
        sigc::signal<void,float>& sig_scoreChanged();
        sigc::signal<void,float>& sig_progressChanged();

    protected:
        void internal_setState(GameState state);
};

#endif /* GAME_H_ */
