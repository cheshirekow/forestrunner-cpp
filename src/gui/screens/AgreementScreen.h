/*
 *  \file   AgreementPage.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef AGREEMENTPAGE_H_
#define AGREEMENTPAGE_H_

#include "gui/Screen.h"

class AgreementScreen :
    public Screen
{
    public:
        AgreementScreen();
        virtual ~AgreementScreen();

        bool onAccept(const CEGUI::EventArgs &e);

        virtual void exec();


};

#endif /* AGREEMENTPAGE_H_ */
