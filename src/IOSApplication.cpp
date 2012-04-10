/*
 *  \file   IOSApplication.cpp
 *
 *  \date   Apr 9, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "IOSApplication.h"
#include "Application.h"

IOSApplication::IOSApplication()
{
    m_impl = new Application();
}

IOSApplication::~IOSApplication()
{
    delete m_impl;
}

bool IOSApplication::init()
{
    return m_impl->ios_init();
}

bool IOSApplication::step()
{
    return m_impl->ios_step();
}

void IOSApplication::cleanup()
{
    m_impl->ios_cleanup();
}
