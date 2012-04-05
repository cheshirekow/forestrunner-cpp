/*
 *  \file   MeshBuilder.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef MESHBUILDER_H_
#define MESHBUILDER_H_

#include <OgreMesh.h>

namespace meshbuilder
{


void create_grid( Ogre::SceneManager* sceneMgr,
                        const Ogre::String& meshName,
                            float sideLen, int numX, int numY);

}

#endif /* MESHBUILDER_H_ */
