
/*
 *  @file   PickNick.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for PickNick class
 */


#include "PickNick.h"

namespace   stategraph {
namespace       states {



PickNick::PickNick():
    m_btn_finished(-150,60,150,150),
    m_txt_nick(20,"Anon")
{
    m_btn_finished.sig_clicked.connect(
            sigc::mem_fun(*this,&PickNick::onFinished) );
}

void PickNick::activate(Manager& mgr)
{
    State::activate(mgr);
    m_btn_finished.activate(mgr);
    m_txt_nick.activate(mgr);
}

void PickNick::deactivate(Manager& mgr)
{
    State::deactivate(mgr);
    m_btn_finished.deactivate(mgr);
    m_txt_nick.deactivate(mgr);
}

void PickNick::setPanel(const char* overlay, const char* panel)
{
    AnimatedPanel::setPanel(overlay,panel);

    m_textArea   = m_panel->getChild("ForestRunner/Panels/03_nick/text");
    m_textArea->setCaption("Anon");
    m_txt_nick.setElement(m_textArea);
}

void PickNick::innerUpdate(float tpf)
{

}

void PickNick::onFinished()
{
    exit(&sig_finished);
}





} //namespace states
} //namespace stategraph



