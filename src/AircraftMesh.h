/*
 *  \file   AircraftMesh.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef AIRCRAFTMESH_H_
#define AIRCRAFTMESH_H_

#include <OGRE/OgreEntity.h>

class AircraftMesh
{
    private:
        Ogre::MeshPtr m_meshPtr;

    public:
        AircraftMesh(float sideLen);
        ~AircraftMesh();

        Ogre::MeshPtr get_mesh();
};

#endif /* AIRCRAFTMESH_H_ */
