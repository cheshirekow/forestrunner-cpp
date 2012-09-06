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

#include "ForestPatch.h"
#include "forestrunner/keys.h"
#include "forestrunner/game/StateGraph.h"
#include "forestrunner/datastore/DataStore.h"

class Game
{
    protected:
        float   m_density;
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

        int     m_prefRadius;
        int     m_prefDensity;
        int     m_prefSpeed;

        bool    m_advCartoon;
        bool    m_advLighting;
        bool    m_advPatchGrids;
        bool    m_advMainGrid;
        bool    m_advGradientFloor;
        bool    m_advWorldRotate;

        forestrunner::game::StateGraph  m_dispatcher;

        ForestPatch** m_patches;
        std::vector<Ogre::MaterialPtr>  m_materials;
        std::vector<Ogre::MaterialPtr>  m_materials_lighting;
        std::vector<Ogre::Entity*>      m_coloredEntities;

        Ogre::SceneNode*    m_patchRoot;
        Ogre::SceneNode*    m_patchRotate;
        Ogre::SceneManager* m_sceneMgr;

        Ogre::MeshPtr       m_cylinderMesh;
        Ogre::MeshPtr       m_cylinderFrame;
        Ogre::MeshPtr       m_cylinderOutline;

        Ogre::Entity*       m_cylinderFrameEntity;
        Ogre::Entity*       m_cylinderOutlineEntity;

        Ogre::Light*        m_light;


    public:
        sigc::signal<void,float>    sig_score;
        sigc::signal<void>          sig_crashed;
        sigc::signal<void>          sig_paused;

        Game();
        ~Game();

        /// reads the settings from the data store, changes internal model if
        /// necessary
        /**
         *  @param store        model for data storage
         *  @param needsInit    set to true if rendering settings have changed
         *  @param needsNewGame set to true if play settings haved changed
         */
        void readSettings(forestrunner::DataStore* store,
                            bool& needsInit,
                            bool& needsNewGame);

        /// callback for when a setting changes in a datastore
        void valueChanged(forestrunner::Key_t,
                            const forestrunner::datastore::MapEntry& );

        /// calculates values for speed density and radius given the preference
        /// settings
        void calcSettings();

        /// return the number of patches (for use in init loop)
        size_t getNumPatches();

        /// makes necessary changes to whether materials have lighting or not
        void setLighting();

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

        /// set the game speed
        void setSpeed(int i);

        /// set the game density
        void setDensity(int i);

        /// set the game radius
        void setRadius(int i);

        /// initialize a new run of the game
        void initRun();

        /// set the value of the horizontal speed
        void setXSpeed(float xSpeed);

        void setRotation(Ogre::Quaternion& q);


        void createScene(Ogre::SceneManager* sceneMgr,
                            Ogre::SceneNode* patchRoot,
                            Ogre::SceneNode* patchRotate);

        void update_game( Ogre::Real tpf );

        /// return the current score, useful after the game has crashed and we
        /// want to find out what the final score was
        float get_score();

};

#endif /* GAME_H_ */
