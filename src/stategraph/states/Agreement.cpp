
/*
 *  @file   Agreement.cpp
 *
 *  @date   Jun 15, 2012
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  implementation for Agreement class
 */


#include "Agreement.h"

namespace   stategraph {
namespace       states {


Agreement::Agreement():
    m_btn_agree(-340,190,-40,280),
    m_btn_disagree(40,190,340,280)
{
    m_btn_agree.sig_clicked.connect(
            sigc::mem_fun(*this,&Agreement::onAgree) );
    m_btn_disagree.sig_clicked.connect(
            sigc::mem_fun(*this,&Agreement::onDisagree) );
}

void Agreement::activate(Manager& mgr)
{
    State::activate(mgr);
    m_btn_agree.activate(mgr);
    m_btn_disagree.activate(mgr);
}

void Agreement::deactivate(Manager& mgr)
{
    State::deactivate(mgr);
    m_btn_agree.deactivate(mgr);
    m_btn_disagree.deactivate(mgr);
}

void Agreement::innerUpdate(float tpf)
{

}

void Agreement::onAgree()
{
    exit(&sig_agree);
}

void Agreement::onDisagree()
{
    std::cerr << "You must agree" << std::endl;
}








} //namespace states
} //namespace stategraph



