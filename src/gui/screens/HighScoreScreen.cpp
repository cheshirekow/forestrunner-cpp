/*
 *  \file   HighScoreScreen.cpp
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "HighScoreScreen.h"
#include "game/Game.h"
#include "forestrunner/util/Printf.hpp"
#include <ctime>

HighScoreScreen::HighScoreScreen()
{
    CEGUI::WindowManager &wmgr  = CEGUI::WindowManager::getSingleton();
    m_root = wmgr.loadLayoutFromFile("highscore.layout");
    m_anim_enter = "FlyIn";
    m_anim_exit  = "FlyOut";

    CEGUI::Window* btn;
    btn = m_root->getChild("Panel/btn_again");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onAgain,
                                this) );
    m_btn_again = btn;

    btn = m_root->getChild("Panel/btn_difficulty");
    btn->subscribeEvent(CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                                &HighScoreScreen::onChange,
                                this) );
    m_btn_difficulty = btn;

    m_lb_userScores = static_cast<CEGUI::Listbox*>(
                        m_root->getChild("Panel/lb_user") );

    m_lb_globalScores = static_cast<CEGUI::Listbox*>(
                        m_root->getChild("Panel/lb_global") );
}

HighScoreScreen::~HighScoreScreen()
{

}

void HighScoreScreen::disableAll()
{
    m_btn_again     ->setEnabled(false);
    m_btn_difficulty->setEnabled(false);

}

void HighScoreScreen::enableAll()
{
    m_btn_again     ->setEnabled(true);
    m_btn_difficulty->setEnabled(true);
}

bool HighScoreScreen::onAgain(const CEGUI::EventArgs &e)
{
    disableAll();
    m_cnx = m_dispatcher->sig_cycleFinished.connect(
            sigc::mem_fun(*this,&HighScoreScreen::onInitFinished) );
    m_dispatcher->startInitRun();
    return true;
}


bool HighScoreScreen::onChange(const CEGUI::EventArgs &e)
{
    disableAll();
    m_sig_transition.emit("paused");
    return true;
}

void HighScoreScreen::exec()
{
    m_lb_userScores->resetList();
    m_lb_globalScores->resetList();

    m_dataStore->write_score(m_game->get_score());
    m_dataStore->sync_scores();

    const char* titleFmt = "%-20s %10s";
    const char* itemFmt  = "%-20s %10.2f";
    const char* dateFmt  = "%m/%d %H:%M";
    char  dateStr[64];

    CEGUI::ListboxTextItem* item;

    item = new CEGUI::ListboxTextItem(
                        m_printf(titleFmt,"Date","Score"),
                        -2,0,true,true) ;
    item->setFont("FreeMono-12");
    m_lb_userScores->addItem( item );


    item = new CEGUI::ListboxTextItem(
                        m_printf(titleFmt,"------------------","--------"),
                        -1,0,true,true) ;
    item->setFont("FreeMono-12");
    m_lb_userScores->addItem(item);

    forestrunner::DataStore::UserVec_t::const_iterator iUserRow;
    for( iUserRow = m_dataStore->userScores().begin();
            iUserRow != m_dataStore->userScores().end();
            iUserRow++ )
    {
        strftime(dateStr,64,dateFmt,localtime(&iUserRow->date));
        const char* rowStr  = m_printf(itemFmt,
                                    dateStr,
                                    iUserRow->score );

        CEGUI::ListboxTextItem* item = new
            CEGUI::ListboxTextItem(rowStr,iUserRow->id,0,false,true);
        item->setSelectionColours(CEGUI::Colour(1.0f,0.5f,0.5f,1.0f));
        item->setSelected(iUserRow->isCurrent);
        item->setFont("FreeMono-12");
        if(iUserRow->isCurrent)
            item->setTextColours(CEGUI::Colour(1.0f,0.5f,0.5f,1.0f));
        m_lb_userScores->addItem(item);
    }

    enableAll();
}


void HighScoreScreen::onInitFinished()
{
    m_cnx.disconnect();
    m_sig_transition.emit("countdown3");
}
