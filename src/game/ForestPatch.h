/*
 *  \file   ForestPatch.h
 *
 *  \date   Apr 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTPATCH_H_
#define FORESTPATCH_H_

#include <vector>
#include <OgreEntity.h>

class ForestPatch
{
    private:
        int     m_maxNodes;
        int     m_nTrees;
        int     m_id;
        float   m_width;
        float   m_height;

        Ogre::SceneNode*                m_patchNode;
        std::vector<Ogre::SceneNode*>   m_cylinderNodes;

    public:
        ForestPatch(Ogre::SceneManager* sceneMgr,
                    Ogre::SceneNode* patchRoot,
                        int id,
                        float width,
                        float height,
                        int maxNodes=100);
        ~ForestPatch();

        void init(std::vector<Ogre::Entity*>& m_cylinders,
                    Ogre::Entity* m_cylinderFrame,
                    Ogre::Entity* m_cylinderOutline );
        void clear(Ogre::SceneManager* sceneMgr);
        void generateLayout(float density);

        Ogre::SceneNode* getRoot();
        bool collision(float x, float y, float r);

        static int getPoisson(float lambda);
};

#endif /* FORESTPATCH_H_ */
