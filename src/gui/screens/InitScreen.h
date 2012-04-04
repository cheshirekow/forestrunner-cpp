/*
 *  \file   InitScreen.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef INITSCREEN_H_
#define INITSCREEN_H_

#include "gui/Screen.h"

class InitScreen :
    public Screen
{
    public:
        InitScreen();
        virtual ~InitScreen();

        virtual void exec();
};

#endif /* INITSCREEN_H_ */
