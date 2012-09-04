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
#include <iostream>

Game::Game()
{
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
    m_patchWidth    = 30.1f; //20.1f;
    m_patchHeight   = 30.1f; //20.1f;

    m_patchDimX = 5;
    m_patchDimY = 8; //4;

    size_t nPatches = m_patchDimX*m_patchDimY;
    m_patches = new ForestPatch* [nPatches];

    m_acSide    = 0.3f;
    m_acRadius  = (m_acSide/2.0f) * (float)std::tan(M_PI/6.0);
    m_acTrans   = (float)( m_acSide*std::sin(M_PI/3) ) - m_acRadius;


    m_cylinderMesh.setNull();
    m_cylinderFrame.setNull();
    m_cylinderOutline.setNull();

    m_cylinderFrameEntity   = 0;
    m_cylinderOutlineEntity = 0;

}





Game::~Game()
{
    delete [] m_patches;
}


size_t Game::getNumPatches()
{
    return m_patchDimX*m_patchDimY;
}


void Game::destroyCylinderMeshes()
{
    std::cerr << "removing meshes" << std::endl;
    Ogre::MeshManager& meshMgr = Ogre::MeshManager::getSingleton();
    if( !meshMgr.getByName("Cylinder").isNull() )
        meshMgr.remove("Cylinder");

    if( !meshMgr.getByName("CylinderFrame").isNull() )
        meshMgr.remove("CylinderFrame");

    if( !meshMgr.getByName("CylinderOutline").isNull() )
        meshMgr.remove("CylinderOutline");

    for( int i=0; i < m_coloredEntities.size(); i++)
        m_sceneMgr->destroyEntity(m_coloredEntities[i]);

    if(m_cylinderFrameEntity)
    {
        m_sceneMgr->destroyEntity(m_cylinderFrameEntity);
        m_cylinderFrameEntity = 0;
    }

    if(m_cylinderOutlineEntity)
    {
        m_sceneMgr->destroyEntity(m_cylinderOutlineEntity);
        m_cylinderOutlineEntity = 0;
    }

    m_coloredEntities.clear();
}

void Game::createCylinderMeshes()
{
    std::cerr << "creating meshes" << std::endl;
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
    std::cerr << "clearing patch " << i << std::endl;
    m_patches[i]->clear(m_sceneMgr);
}

void Game::initPatch(int i)
{
    std::cerr << "initializing patch " << i << std::endl;
    m_patches[i]->init(m_coloredEntities,
                        m_cylinderFrameEntity,
                        m_cylinderOutlineEntity);
}


void Game::setSpeed(int i)
{
    m_ySpeed    = 20.0f + i*5.0f;
}

void Game::setDensity(int i)
{
    m_density   = 3.0f + i*2.0f;;
}

void Game::setRadius(int i)
{
    m_radius    = 0.5f + i*0.3f;
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
    m_patchRoot->setPosition(m_xPos,0,m_yPos);
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









bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    return true;
}





bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}






void Game::update_game( Ogre::Real tpf )
{
    m_score += tpf;
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
    {
        sig_crashed.emit();
    }

    sig_score.emit(m_score);
}






