/*
 *  \file   CEGUIDummyLogger.cpp
 *
 *  \date   Apr 10, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "CEGUIDummyLogger.h"


namespace CEGUI
{



DummyLogger::DummyLogger()
{
    // TODO Auto-generated constructor stub

}

DummyLogger::~DummyLogger()
{
    // TODO Auto-generated destructor stub
}


void DummyLogger::logEvent( const String& message, LoggingLevel level)
{
    std::cerr << message << std::endl;
}




void DummyLogger::setLogFilename( const String& filename, bool append)
{
    std::cerr << "Dummy logger doesn't write to file, ignoring filename: "
                << filename << std::endl;
}




}
