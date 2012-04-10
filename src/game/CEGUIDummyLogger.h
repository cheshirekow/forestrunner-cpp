/*
 *  \file   CEGUIDummyLogger.h
 *
 *  \date   Apr 10, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CEGUIDUMMYLOGGER_H_
#define CEGUIDUMMYLOGGER_H_

#include "CEGUILogger.h"
#include <iostream>

namespace CEGUI
{

class DummyLogger :
    public Logger
{
    public:
        DummyLogger();
        virtual ~DummyLogger();

        virtual void logEvent( const String& message, LoggingLevel level=Standard);
        virtual void setLogFilename( const String& filename, bool append=false);
};


}

#endif /* CEGUIDUMMYLOGGER_H_ */
