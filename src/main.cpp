/*
 *  \file   main.cpp
 *
 *  \date   Apr 9, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/desktop/Application.h"
#include "forestrunner/desktop/DataStore.h"

int main(int argc, char *argv[])
{
    // Create a datastore object
    forestrunner::desktop::DataStore store;

    // Create application object
    forestrunner::desktop::Application app;

    try
    {
        store.init();
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
