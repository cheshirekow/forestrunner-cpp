
/*
 *  @file   Initialize.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for Initialize class
 */


#include "Initialize.h"

namespace   stategraph {
namespace       states {



Initialize::Initialize():
    m_step(0)
{

}



void Initialize::innerUpdate(float tpf)
{
    switch(m_step)
    {
        // step one, get a pointer to slider panels
        case 0:
        {
            m_circle =
                m_panel->getChild("ForestRunner/Panels/01_loading/circle");
            m_step++;
            break;
        }

        case s_lastStep:
        {
            exit(&sig_finished);
            break;
        }

        default:
            m_step++;
            m_circle->_setLeft( (138 + (m_step/(float)s_lastStep)*600)/m_panel->getWidth() );
            break;
    }
}







} //namespace states
} //namespace stategraph



