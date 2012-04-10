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

#ifdef OGRE_IS_IOS
    obj->begin("ForestRunner/BlackWireframe",
                    Ogre::RenderOperation::OT_POINT_LIST);
#else
    obj->begin("ForestRunner/BlackWireframe",
                    Ogre::RenderOperation::OT_LINE_LIST);
#endif

    // this is the length of a single grid line
    float verticalLength    = sideLen*(numY);
    float horizontalLength  = sideLen*(numX);

    // first create all the vertical lines
    int idx = 0;
    for(int ix=0; ix < numX+1; ix++)
    {
        float x = ix*sideLen;
        obj->position(x, 0, 0);
        obj->position(x, 0, -verticalLength);

        obj->index(idx++);
        obj->index(idx++);
    }

    // then the horizontal
    for(int iy=0; iy < numY+1; iy++)
    {
        float y = iy*sideLen;
        obj->position(0,                0, -y);
        obj->position(horizontalLength, 0, -y);

        obj->index(idx++);
        obj->index(idx++);
    }

    obj->end();

    MeshPtr mesh = obj->convertToMesh(meshName);

    sceneMgr->destroyManualObject(obj);
}


void create_cylinder( Ogre::SceneManager* sceneMgr,
                        const Ogre::String& meshName,
                            float radius,
                            float height,
                            int   axisSamples,
                            int   radialSamples,
                            bool  cap,
                            bool  invert)
{
    using namespace Ogre;

    ManualObject* obj=  sceneMgr->createManualObject("cylinder");

    if(invert)
        obj->begin("ForestRunner/Black",
                    Ogre::RenderOperation::OT_TRIANGLE_LIST);
    else
        obj->begin("ForestRunner/BlackWireframe",
                    Ogre::RenderOperation::OT_TRIANGLE_LIST);


    for(int iHeight=0; iHeight < axisSamples; iHeight++)
    {
        float h = iHeight*height/(axisSamples-1);
        if(invert)
            h -= 0.1f;

        for(int iAngle=0; iAngle < radialSamples; iAngle++)
        {
            float a = iAngle*2*M_PI/radialSamples;
            float x = radius * std::cos(a);
            float y = radius * std::sin(a);
            obj->position(x,    h,      y);
        }
    }

    if(cap)
    {
        obj->position(0,0,0);
        obj->position(0,height,0);
    }

    // for each horizontal layer except the last
    for(int h=0; h < axisSamples-1; h++)
    {
        // for each radial vertex except the last
        for(int r=0; r < radialSamples; r++)
        {
            int i[2];
            int j[2];

            for(int k=0; k < 2; k++)
            {
                i[k] = (  h   *radialSamples)   + ( (r+k) % radialSamples );
                j[k] = ( (h+1)*radialSamples)   + ( (r+k) % radialSamples );
            }



            if(invert)
            {
                // create triangle with two bottom verteces and one
                // top vertex
                obj->index(i[0]);
                obj->index(i[1]);
                obj->index(j[0]);

                // create triangle with one bottom vertex and two
                // top vertices
                obj->index(j[1]);
                obj->index(j[0]);
                obj->index(i[1]);
            }

            else
            {
                obj->index(j[0]);
                obj->index(i[1]);
                obj->index(i[0]);

                obj->index(i[1]);
                obj->index(j[0]);
                obj->index(j[1]);
            }

        }
    }

    // close up the bottom
    if( cap )
    {
        int iCaps       =  axisSamples*radialSamples;
        int iOffset[2];

        iOffset[0] = 0;
        iOffset[1] = (axisSamples-1)*radialSamples;

        for(int h=0; h < 2; h++)
        {
            int j = iCaps + h;

            for(int r=0; r < radialSamples; r++)
            {
                int i[2];

                for(int k=0; k < 2; k++)
                    i[k] = iOffset[h] + ( (r+k) % radialSamples );

                int h2 = invert ? (h+1) % 2 : h;

                // create triangle between two vertices and the the center
                // of the circle
                if(h2 > 0)
                {
                    obj->index(j);
                    obj->index(i[1]);
                    obj->index(i[0]);
                }
                else
                {
                    obj->index(i[0]);
                    obj->index(i[1]);
                    obj->index(j);
                }
            }
        }

    }

    obj->end();

    MeshPtr mesh = obj->convertToMesh(meshName);

    sceneMgr->destroyManualObject(obj);
}






void create_cylinder_wire( Ogre::SceneManager* sceneMgr,
                        const Ogre::String& meshName,
                            float radius,
                            float height,
                            int   radialSamples)
{
    using namespace Ogre;

    ManualObject* obj=  sceneMgr->createManualObject("cylinder");

    obj->begin("ForestRunner/BlackWireframe",
                    Ogre::RenderOperation::OT_LINE_LIST);


    for(int iHeight=0; iHeight < 2; iHeight++)
    {
        float h = iHeight*height;

        for(int iAngle=0; iAngle < radialSamples; iAngle++)
        {
            float a = iAngle*2*M_PI/radialSamples;
            float x = radius * std::cos(a);
            float y = radius * std::sin(a);
            obj->position(x,    h,      y);
        }
    }

    // for each horizontal layer except the last
    for(int h=0; h < 2; h++)
    {
        // for each radial vertex except the last
        for(int r=0; r < radialSamples; r++)
        {
            for(int k=0; k < 2; k++)
            {
                int i = (  h   *radialSamples)   + ( (r+k) % radialSamples );
                obj->index(i);
            }
        }
    }

    obj->end();

    MeshPtr mesh = obj->convertToMesh(meshName);

    sceneMgr->destroyManualObject(obj);
}






}
