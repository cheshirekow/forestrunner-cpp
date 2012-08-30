/*
 *  \file   IOSApplication.h
 *
 *  \date   Apr 9, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef IOSAPPLICATION_H_
#define IOSAPPLICATION_H_

class Application;

class IOSApplication
{
    private:
        Application* m_impl;

    public:
        IOSApplication();
        ~IOSApplication();

        bool init();
        bool step();
        void cleanup();
};

#endif /* IOSAPPLICATION_H_ */