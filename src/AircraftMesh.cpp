/*
 *  \file   AircraftMesh.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "AircraftMesh.h"


#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>


AircraftMesh::AircraftMesh(float sideLen)
{
    using namespace Ogre;

    float y       = (float) std::sqrt( sideLen*sideLen
                                    - (sideLen/2.0f)*(sideLen/2.0f) );
    float x       = sideLen/2.0f;
    float height  = 0.1f;

    /*
    Vector3f[] vertices = new Vector3f[4];
    vertices[0] = new Vector3f(0f,0f,0f);
    vertices[1] = new Vector3f(-x,0,y);
    vertices[2] = new Vector3f(x,0,y);
    vertices[3] = new Vector3f(0,height,y);

    int[]      indexes  = { 0,2,1, 0,1,3, 1,2,3, 2,0,3 };
    */

    Vector3 v[4]; // vertices
    v[0] = Vector3(0.0f,    0.0f,   0.0f);
    v[1] = Vector3(-x,      y,      0.0f);
    v[2] = Vector3(x,       y,      0.0f);
    v[3] = Vector3(0,       y,      height);

    Vector3 n[4]; // normals
    for(int i=0; i < 4; i++)
        n[i] = v[i].normalisedCopy();

    // Create the mesh via the MeshManager
    MeshPtr msh = MeshManager::getSingleton().createManual(
                                                "RunnerAircraft", "General");

    // Create one submesh
    SubMesh* sub = msh->createSubMesh();

    /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
    const size_t nVertices = 4;
    const size_t stride    = 3*2;
    const size_t vbufCount = stride*nVertices;

    float vertices[vbufCount];
    for(int i=0; i < nVertices; i++)
    {
        float* vp = vertices + i*stride;
        float* np = vp + 3;

        for(int j=0; j < 3; j++)
        {
            vp[j] = v[i][j];
            np[j] = n[i][j];
        }
    }

    RenderSystem* rs = Root::getSingleton().getRenderSystem();
    RGBA colours[nVertices];
    RGBA *pColour = colours;
    // Use render system to convert colour value since colour packing varies
    rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
    rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
    rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
    rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour

    /// Define 12 triangles (two triangles per cube face)
    /// The values in this table refer to vertices in the above table
    const size_t ibufCount = 12;
    unsigned short faces[ibufCount] =
    {
            0,2,1,
            0,1,3,
            1,2,3,
            2,0,3
    };

    /// Create vertex data structure for 4 vertices shared between submeshes
    msh->sharedVertexData = new VertexData();
    msh->sharedVertexData->vertexCount = nVertices;

    /// Create declaration (memory format) of vertex data
    VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;
    // 1st buffer
    decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
    offset += VertexElement::getTypeSize(VET_FLOAT3);

    decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
    offset += VertexElement::getTypeSize(VET_FLOAT3);

    /// Allocate vertex buffer of the requested number of vertices (vertexCount)
    /// and bytes per vertex (offset)
    HardwareVertexBufferSharedPtr vbuf =
        HardwareBufferManager::getSingleton().createVertexBuffer(
                                        offset,
                                        nVertices,
                                        HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

    /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
    VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding;
    bind->setBinding(0, vbuf);

    // 2nd buffer
    offset = 0;
    decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
    offset += VertexElement::getTypeSize(VET_COLOUR);

    /// Allocate vertex buffer of the requested number of vertices (vertexCount)
    /// and bytes per vertex (offset)
    vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
                                        offset,
                                        msh->sharedVertexData->vertexCount,
                                        HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);

    /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
    bind->setBinding(1, vbuf);

    /// Allocate index buffer of the requested number of vertices (ibufCount)
    HardwareIndexBufferSharedPtr ibuf =
            HardwareBufferManager::getSingleton().createIndexBuffer(
                                        HardwareIndexBuffer::IT_16BIT,
                                        ibufCount,
                                        HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    /// Upload the index data to the card
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

    /// Set parameters of the submesh
    sub->useSharedVertices = true;
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = ibufCount;
    sub->indexData->indexStart = 0;

    /// Set bounding information (for culling)
    msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
    msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));

    /// Notify -Mesh object that it has been loaded
    msh->load();

    m_meshPtr = msh;
}

AircraftMesh::~AircraftMesh()
{
    // TODO Auto-generated destructor stub
}


Ogre::MeshPtr AircraftMesh::get_mesh()
{
    return m_meshPtr;
}
