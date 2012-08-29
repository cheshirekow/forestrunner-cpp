/*
 *  \file   main.cpp
 *
 *  \date   Apr 9, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "app/Application.h"


int main(int argc, char *argv[])
{
    // Create application object
    Application app;

    try
    {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
