/*
 *  \file   ForestPatch.cpp
 *
 *  \date   Apr 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "game/ForestPatch.h"

#include <cmath>
#include <cstdlib>

#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <sstream>

ForestPatch::ForestPatch(Ogre::SceneManager* sceneMgr,
                            Ogre::SceneNode* patchRoot,
                            int id,
                            float width,
                            float height,
                            int maxNodes):
    m_maxNodes(maxNodes),
    m_nTrees(0),
    m_id(id),
    m_width(width),
    m_height(height)
{
    m_patchNode = patchRoot->createChildSceneNode();
    for(int i=0; i < maxNodes; i++)
        m_cylinderNodes.push_back( sceneMgr->createSceneNode() );
}

ForestPatch::~ForestPatch()
{

}

void ForestPatch::init(std::vector<Ogre::Entity*>& m_cylinders,
                    Ogre::Entity* m_cylinderFrame,
                    Ogre::Entity* m_cylinderOutline )
{
    for(int i=0; i < m_maxNodes; i++)
    {
        std::stringstream sstream;
        sstream << "cylinder_" << m_id << "_" << i;

        int j = std::rand() % m_cylinders.size();
        m_cylinderNodes[i]->attachObject(
                m_cylinders[j]->clone( sstream.str()) );


        sstream.str("");
        sstream << "cylinderFrame_" << m_id << "_" << i;
        m_cylinderNodes[i]->attachObject(
                m_cylinderFrame->clone( sstream.str()) );

        sstream.str("");
        sstream << "cylinderOutline_" << m_id << "_" << i;
        m_cylinderNodes[i]->attachObject(
                m_cylinderOutline->clone( sstream.str()) );
    }
}



void ForestPatch::clear(Ogre::SceneManager* sceneMgr)
{
    m_patchNode->removeAllChildren();
    m_nTrees = 0;

    for(int i=0; i < m_maxNodes; i++)
    {
        m_cylinderNodes[i]->detachAllObjects();

        std::stringstream sstream;
        sstream << "cylinder_" << m_id << "_" << i;
        sceneMgr->destroyEntity( sstream.str() );

        sstream.str("");
        sstream << "cylinderFrame_" << m_id << "_" << i;
        sceneMgr->destroyEntity( sstream.str() );

        sstream.str("");
        sstream << "cylinderOutline_" << m_id << "_" << i;
        sceneMgr->destroyEntity( sstream.str() );
    }
}


void ForestPatch::generateLayout(float density)
{
    m_patchNode->removeAllChildren();

    m_nTrees = getPoisson(density);
    for(int i=0; i < m_nTrees; i++)
    {
        Ogre::SceneNode* child = m_cylinderNodes[i];
        m_patchNode->addChild(child);
        child->setPosition( m_width * std::rand() / RAND_MAX,
                            0.01f * std::rand() / RAND_MAX,
                            m_height * std::rand() / RAND_MAX );

    }
}

Ogre::SceneNode* ForestPatch::getRoot()
{
    return m_patchNode;
}

bool ForestPatch::collision(float x, float y, float r)
{
    float r2    = r*r;

    for(int i=0; i < m_nTrees; i++)
    {
        Ogre::Vector3 t = m_cylinderNodes[i]->convertWorldToLocalPosition(Ogre::Vector3::ZERO);
        //System.out.println("   " + t);
        float d2  = t.x*t.x + t.z*t.z;

        if(d2 < r2)
            return true;
    }

    return false;
}

int ForestPatch::getPoisson(float lambda)
{
    double L = std::exp(-lambda);
    double p = 1.0;
    int k = 0;

    do
    {
        k++;
        p *= std::rand() / (double) RAND_MAX;
    } while (p > L);

    return k - 1;
}

