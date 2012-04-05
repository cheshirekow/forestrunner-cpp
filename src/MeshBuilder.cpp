/*
 *  \file   MeshBuilder.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "MeshBuilder.h"

#include <OgreSceneManager.h>
#include <OgreManualObject.h>


namespace meshbuilder
{


void create_grid( Ogre::SceneManager* sceneMgr,
                        const Ogre::String& meshName,
                            float sideLen, int numX, int numY)
{
    using namespace Ogre;

    ManualObject* obj=  sceneMgr->createManualObject("grid");

    obj->begin("ForestRunner/BlackWireframe",
                    Ogre::RenderOperation::OT_LINE_LIST);

    // this is the length of a single grid line
    float verticalLength    = sideLen*(numY);
    float horizontalLength  = sideLen*(numX);

    // first create all the vertical lines
    for(int ix=0; ix < numX+1; ix++)
    {
        float x = ix*sideLen;
        obj->position(x, 0, 0);
        obj->position(x, 0, -verticalLength);
    }

    // then the horizontal
    for(int iy=0; iy < numY+1; iy++)
    {
        float y = iy*sideLen;
        obj->position(0,                0, -y);
        obj->position(horizontalLength, 0, -y);
    }

    obj->end();

    MeshPtr mesh = obj->convertToMesh(meshName);

    sceneMgr->destroyManualObject(obj);
}









}
