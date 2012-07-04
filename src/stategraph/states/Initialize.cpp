
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
            m_rectangle =
                m_panel->getChild("ForestRunner/Panels/01_loading/rectangle");
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

            float w = m_circle->getWidth() / s_viewport->getActualWidth();
            float p = (m_step/(float)s_lastStep);
            float c = (1-p)*s_start + p*s_end;
            float cn= c / s_viewport->getActualWidth();

            float rw= p*600 / s_viewport->getActualWidth();

            m_circle->_setLeft( cn - w/2 );
            m_rectangle->_setWidth(rw);
            break;
    }
}







} //namespace states
} //namespace stategraph



