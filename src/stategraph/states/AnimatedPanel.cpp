
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
}

void AnimatedPanel::update(float tpf, Manager& mgr)
{
    switch(m_step)
    {
        // first step is initialize the animation
        case 0:
        {
            m_panel->_setTop( -1.5 );
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
                m_panel->_setTop(-0.5);
                m_t = 0;
                m_step++;
                break;
            }

            float y = 1.5 - x*x;
            std::cerr << "Step 1, t: " << m_t  << " y: " << y << std::endl;
            m_panel->_setTop(-y);
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
            if(x < 0)
            {
                m_panel->_setTop(0.5);
                m_t = 0;
                m_step++;
                break;
            }

            float y = x*x + 0.5;
            m_panel->_setTop(-y );
            break;

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



