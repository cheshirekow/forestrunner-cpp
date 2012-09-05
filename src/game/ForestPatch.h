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
        bool    m_hasOutline;

        Ogre::SceneNode*                m_patchNode;
        std::vector<Ogre::SceneNode*>   m_cylinderNodes;

    public:
        /// initializes data members and generates scene nodes for each of the
        /// cylinders
        /**
         *  @param sceneMgr     scene manager for the game
         *  @param patchRoot    the root node to attach this patch scene node
         *                      to
         *  @param id           integer id of this patch
         *  @param width        the width (in render units) of this patch
         *  @param height       the height (in render units) of this patch
         *  @param maxNodes     the maximum number of trees in this patch
         *
         *  @note the constructor creates scene nodes for each cylinder, but
         *  does nothing else
         */
        ForestPatch(Ogre::SceneManager* sceneMgr,
                    Ogre::SceneNode* patchRoot,
                        int id,
                        float width,
                        float height,
                        int maxNodes=100);

        /// Does nothing, really
        ~ForestPatch();

        /// attaches a cylinder outline, cylinder mesh, and cylinder frame to
        /// one of each of the cylinder scene nodes that compose this
        /// forest patch
        /**
         *  @param cylinders        array of (colored) cylinder meshes
         *  @param cylinderFrame    wireframe cylinder
         *  @param cylinderOutline  inverted cylinder to draw as an outline
         *
         *  @note does not layout the cylinders or choose how many are in the
         *        patch, so it is safe to call this mid-game if
         *        settings change
         */
        void init(std::vector<Ogre::Entity*>& cylinders,
                    Ogre::Entity* cylinderFrame,
                    Ogre::Entity* cylinderOutline );

        /// removes all cylinder scene nodes from the patch, and removes all
        /// entities from each cylinder scene node
        void clear(Ogre::SceneManager* sceneMgr);

        /// generates tree locations, and sets the position of the cylinder
        /// scene nodes for each tree location
        /**
         *  @param density  density of the forest (parameter of poisson
         *                  distribution)
         *
         *  @note  before generating tree positions, this method first removes
         *         all children from the patch scene node, and then re-adds
         *         children after generating a random number for the number
         *         of trees in this patch
         */
        void generateLayout(float density);

        /// return the scene node that is the root of this forest patch
        Ogre::SceneNode* getRoot();

        /// return true if the vehicle is in collision with a tree
        /**
         *  @param x    x-position of vehicle centroid
         *  @param y    y-position of vehicle centroid
         *  @param r    vehicle radius (assuming disk)
         */
        bool collision(float x, float y, float r);

        /// generate a random integer poisson distributed with parameter
        /// lambda.
        static int getPoisson(float lambda);
};

#endif /* FORESTPATCH_H_ */
