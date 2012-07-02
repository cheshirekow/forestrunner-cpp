
/*
 *  @file   Manager.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for Manager class
 */


#include "Manager.h"

namespace   stategraph {


void Manager::update(float tpf)
{
    sig_update.emit(tpf,*this);
}







} //namespace stategraph



