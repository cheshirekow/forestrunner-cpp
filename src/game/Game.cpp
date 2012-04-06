/*
 *  \file   Game.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "Game.h"

#include <cmath>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreMaterialManager.h>

#include "MeshBuilder.h"

Game::Game()
{
    m_gameState = GS_CRASHED;

    m_xAccel    = 50.0f;
    m_xSpeedMax = 20.0f;
    m_xSpeed    = 0.0f;
    m_ySpeed    = 20.0f;
    m_density   = 5.0f;

    m_radius    = 0.5f;
    m_height    = 3.0f;
    m_outline   = 0.1f;

    m_xPos      = 0;
    m_yPos      = 0;
    m_patchWidth    = 20.1f; //20.1f;
    m_patchHeight   = 20.1f; //20.1f;

    m_patchDimX = 5;
    m_patchDimY = 8; //4;

    size_t nPatches = m_patchDimX*m_patchDimY;
    m_patches = new ForestPatch* [nPatches];
    m_init.setNumPatches(nPatches);

    m_acSide    = 0.3f;
    m_acRadius  = (m_acSide/2.0f) * (float)std::tan(M_PI/6.0);
    m_acTrans   = (float)( m_acSide*std::sin(M_PI/3) ) - m_acRadius;

    m_init.sig_clearPatch.connect(
            sigc::mem_fun(*this,&Game::clearPatch) );
    m_init.sig_freeMeshes.connect(
            sigc::mem_fun(*this,&Game::destroyCylinderMeshes) );
    m_init.sig_createMeshes.connect(
            sigc::mem_fun(*this,&Game::createCylinderMeshes) );
    m_init.sig_initPatch.connect(
            sigc::mem_fun(*this,&Game::initPatch) );
    m_init.sig_initRun.connect(
            sigc::mem_fun(*this,&Game::initRun ) );
    m_init.sig_done.connect(
            sigc::mem_fun(*this,&Game::initFinished) );
    m_init.sig_progress.connect(
            sigc::mem_fun(*this,&Game::initProgress) );

}





Game::~Game()
{
    delete [] m_patches;
}

void Game::destroyCylinderMeshes()
{
    std::cout << "removing meshes" << std::endl;
    Ogre::MeshManager& meshMgr = Ogre::MeshManager::getSingleton();
    meshMgr.remove("Cylinder");
    meshMgr.remove("CylinderFrame");
    meshMgr.remove("CylinderOutline");
}

void Game::createCylinderMeshes()
{
    std::cout << "creating meshes" << std::endl;
    meshbuilder::create_cylinder(m_sceneMgr,
                                    "Cylinder",
                                    m_radius,
                                    m_height,
                                    2,20,true);

    meshbuilder::create_cylinder(m_sceneMgr,
                                    "CylinderOutline",
                                    m_radius+m_outline,
                                    m_height+2*m_outline,
                                    2,20,true,true);

    meshbuilder::create_cylinder_wire(m_sceneMgr,
                                    "CylinderFrame",
                                    m_radius,
                                    m_height,20);
    Ogre::MeshManager& meshMgr = Ogre::MeshManager::getSingleton();
    m_cylinderMesh      = meshMgr.getByName("Cylinder");
    m_cylinderFrame     = meshMgr.getByName("CylinderFrame");
    m_cylinderOutline   = meshMgr.getByName("CylinderOutline");

    m_cylinderFrameEntity   =
            m_sceneMgr->createEntity("CylinderFrame","CylinderFrame");
    m_cylinderOutlineEntity =
            m_sceneMgr->createEntity("CylinderOutline","CylinderOutline");

    for( int i=0; i < m_materials.size(); i++)
    {
        Ogre::Entity* entity =
            m_sceneMgr->createEntity("Cylinder");
        entity->setMaterial(m_materials[i]);
        m_coloredEntities.push_back(entity);
    }
}

void Game::clearPatch(int i)
{
    m_patches[i]->clear(m_sceneMgr);
}

void Game::initPatch(int i)
{
    m_patches[i]->init(m_coloredEntities,
                        m_cylinderFrameEntity,
                        m_cylinderOutlineEntity);
}

void Game::initFinished()
{
    internal_setState(GS_COUNTDOWN);
}

void Game::initProgress(float progress)
{
    m_sig_progressChanged.emit(progress);
}

void Game::initRun()
{
    m_xSpeed    = 0.0f;
    m_xPos      = 0;
    m_yPos      = 0;
    m_score     = 0;

    int k=0;
    for(int i=0; i < m_patchDimX; i++)
    {
        for(int j=0; j < m_patchDimY; j++)
        {
            k = (i*m_patchDimY) + j;
            ForestPatch*     patch = m_patches[k];
            Ogre::SceneNode* node = patch->getRoot();
            node->setPosition(
                    (i-m_patchDimX/2.0f)*m_patchWidth,
                    0.0f,
                    -j*m_patchHeight );
            patch->generateLayout(m_density);
        }
    }

    m_patchRotate->setOrientation(Ogre::Quaternion::IDENTITY);
}

void Game::createScene(Ogre::SceneManager* sceneMgr,
                            Ogre::SceneNode* patchRoot,
                            Ogre::SceneNode* patchRotate)
{
    m_sceneMgr      = sceneMgr;
    m_patchRoot     = patchRoot;
    m_patchRotate   = patchRotate;

    Ogre::MaterialManager& mgr = Ogre::MaterialManager::getSingleton();
    m_materials.push_back( mgr.getByName("ForestRunner/Red") );
    m_materials.push_back( mgr.getByName("ForestRunner/Yellow") );

    size_t nPatches = m_patchDimX*m_patchDimY;
    for(int i=0; i < nPatches; i++)
        m_patches[i] = new ForestPatch(sceneMgr,patchRoot,i,
                                        m_patchWidth,m_patchHeight);
}





GameState Game::getState()
{
    return m_gameState;
}





void Game::setState(GameState state)
{
    m_gameState = state;

    if(state == GS_INIT)
        m_init.reset();

}





bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    return true;
}





bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}









void Game::update( Ogre::Real tpf )
{
    if(m_gameState == GS_INIT)
        m_init.step();

    if(m_gameState != GS_RUNNING)
        return;

    m_score += tpf;
    m_sig_scoreChanged.emit(m_score);
    updateSpeed(tpf);

    m_yPos += m_ySpeed*tpf;
    m_xPos -= m_xSpeed*tpf;

    if(m_xPos > m_patchWidth)
    {
        m_xPos -= m_patchWidth;

        int k1,k2;
        for(int j=0; j < m_patchDimY; j++)
        {
            k1 = (m_patchDimX-1)*m_patchDimY + j;
            ForestPatch* temp = m_patches[k1];
            for(int i=m_patchDimX-1; i > 0; i--)
            {
                k1 = ( i   *m_patchDimY + j);
                k2 = ((i-1)*m_patchDimY + j);
                ForestPatch* patch = m_patches[k1] = m_patches[k2];
                Ogre::SceneNode* node = patch->getRoot();
                node->setPosition(
                        (i-m_patchDimX/2.0f)*m_patchWidth,
                        0.0f,
                        -j*m_patchHeight );
            }

            m_patches[j] = temp;
            Ogre::SceneNode* node = temp->getRoot();
            node->setPosition(
                        (-m_patchDimX/2.0f)*m_patchWidth,
                        0.0f,
                        -j*m_patchHeight );
        }
    }

    if(m_xPos < -m_patchWidth)
    {
        m_xPos += m_patchWidth;

        int k1,k2;
        for(int j=0; j < m_patchDimY; j++)
        {
            ForestPatch* temp = m_patches[j];
            for(int i=0; i < m_patchDimX-1; i++)
            {
                k1 = ( i   *m_patchDimY + j);
                k2 = ((i+1)*m_patchDimY + j);

                m_patches[k1] = m_patches[k2];
                Ogre::SceneNode* node = m_patches[k1]->getRoot();
                node->setPosition(
                        (i-m_patchDimX/2.0f)*m_patchWidth,
                        0.0f,
                        -j*m_patchHeight );
            }

            k2 = ((m_patchDimX-1)*m_patchDimY + j);
            m_patches[k2] = temp;
            Ogre::SceneNode* node = temp->getRoot();
            node->setPosition(
                    (m_patchDimX/2.0f-1)*m_patchWidth,
                    0.0f,
                    -j*m_patchHeight );
        }
    }

    if(m_yPos > m_patchHeight)
    {
        m_yPos -= m_patchHeight;

        int k=0;
        for(int i=0; i < m_patchDimX; i++)
        {
            ForestPatch* temp = m_patches[i*m_patchDimY];
            for(int j=0; j < m_patchDimY-1; j++)
            {
                k = i*m_patchDimY + j;
                ForestPatch*patch       = m_patches[k] = m_patches[k+1];
                Ogre::SceneNode* node   = patch->getRoot();
                node->setPosition(
                        (i-m_patchDimX/2.0f)*m_patchWidth,
                        0.0f,
                        -j*m_patchHeight );
            }

            m_patches[k+1] = temp;
            Ogre::SceneNode* node   = temp->getRoot();
                node->setPosition(
                        (i-m_patchDimX/2.0f)*m_patchWidth,
                        0.0f,
                        -(m_patchDimY-1)*m_patchHeight );
            temp->generateLayout(m_density);
        }
    }

    m_patchRoot->setPosition(m_xPos,0,m_yPos);

    bool collision = false;
    for( int i=0; i < m_patchDimX && !collision; i++)
    {
        for(int j=0; j < 2 && !collision; j++)
        {
            int k = ( i*m_patchDimY + j );
            collision = m_patches[k]->collision(m_xPos, m_yPos,
                                                m_radius + m_acRadius);
        }
    }

    if(collision)
        internal_setState(GS_CRASHED);
}






sigc::signal<void,GameState>& Game::sig_stateChanged()
{
    return m_sig_stateChanged;
}





sigc::signal<void,float>& Game::sig_scoreChanged()
{
    return m_sig_scoreChanged;
}





sigc::signal<void,float>& Game::sig_progressChanged()
{
    return m_sig_progressChanged;
}





void Game::internal_setState(GameState state)
{
    m_gameState = state;
    m_sig_stateChanged.emit(state);
}
