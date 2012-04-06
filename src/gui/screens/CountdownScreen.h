/*
 *  \file   CountdownScreen.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef COUNTDOWNSCREEN_H_
#define COUNTDOWNSCREEN_H_

#include "gui/Screen.h"

class CountdownScreen :
    public Screen
{
    int         m_which;
    std::string m_next;

    public:
        CountdownScreen(int count);
        virtual ~CountdownScreen();
        virtual void exec();
};

#endif /* COUNTDOWNSCREEN_H_ */
