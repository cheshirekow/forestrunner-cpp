
/*
 *  @file   AnimatedPanel.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for AnimatedPanel class
 */


#include "AnimatedPanel.h"

namespace   stategraph {
namespace       states {



void AnimatedPanel::exit(ExitSignal_t* sig)
{
    m_exitSignal = sig;
    m_step++;
}








AnimatedPanel::AnimatedPanel()
{
    m_step          = 0;
    m_exitSignal    = 0;
    m_duration      = 1;
}


void AnimatedPanel::setPanel(const char* overlay, const char* panel)
{
   m_overlay = Ogre::OverlayManager::getSingleton().getByName(overlay);
   m_panel   = m_overlay->getChild(panel);

   float height = m_panel->getHeight() / s_viewport->getActualHeight();

   std::cerr << "Screen height of " << panel << " is " << height << std::endl;

   m_topTarget = -height/2.0;
   m_topAbove  = -0.5-height;
   m_topBelow  = 0.5;
}

void AnimatedPanel::update(float tpf, Manager& mgr)
{
    switch(m_step)
    {
        // first step is initialize the animation
        case 0:
        {
            m_panel->_setTop( m_topAbove );
            m_overlay->show();
            m_t = 0;
            m_step++;
            break;
        }

        // second step, animate the entrance
        case 1:
        {
            m_t += tpf;
            float x = m_t/ m_duration;
            if(x > 1)
            {
                m_panel->_setTop(m_topTarget);
                m_t = 0;
                m_step++;
                break;
            }

            float y = x*x;
            m_panel->_setTop( y * m_topTarget + (1-y)*m_topAbove );
            break;
        }

        // middle step, work on the gui, derived class will increment
        // step counter by calling exit()
        case 2:
        {
            innerUpdate(tpf);
            break;
        }

        // next to last step, animate the exit
        case 3:
        {
            m_t += tpf;
            float x = m_t/ m_duration;
            if(x > 1)
            {
                m_panel->_setTop(m_topBelow);
                m_t = 0;
                m_step++;
                break;
            }

            float y = x*x;
            m_panel->_setTop( y * m_topBelow + (1-y)*m_topTarget );
            break;
        }

        // last step transition out
        case 4:
        {
            m_overlay->hide();
            m_exitSignal->emit(mgr);
            m_step = 0;
            deactivate(mgr);
            break;
        }
    }
}













} //namespace states
} //namespace stategraph



