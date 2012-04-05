/*
 *  \file   CrashScreen.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CRASHSCREEN_H_
#define CRASHSCREEN_H_

#include "gui/Screen.h"

class CrashScreen :
    public Screen
{
    public:
        CrashScreen();
        virtual ~CrashScreen();
        virtual void exec();
};

#endif /* CRASHSCREEN_H_ */
