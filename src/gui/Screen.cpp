/*
 *  \file   Screen.cpp
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "Screen.h"
#include "game/Game.h"

Screen::Screen():
    m_root(0),
    m_anim_exit("undefined"),
    m_anim_enter("undefined")
{

}

Screen::~Screen()
{

}

CEGUI::Window* Screen::get_root()
{
    return m_root;
}

const CEGUI::String& Screen::get_anim_exit()
{
    return m_anim_exit;
}

const CEGUI::String& Screen::get_anim_enter()
{
    return m_anim_enter;
}

Screen::TransSignal_t& Screen::sig_transition()
{
    return m_sig_transition;
}


void Screen::set_game(Game* game)
{
    m_game = game;
}

void Screen::exec()
{
    return;
}


