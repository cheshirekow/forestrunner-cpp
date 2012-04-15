/*
 *  \file   Page.h
 *
 *  \date   Apr 4, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <sigc++/sigc++.h>
#include <string>
#include <CEGUI/CEGUI.h>

class Game;

class Screen
{
    public:
        typedef sigc::signal<void, const std::string& > TransSignal_t;

    protected:
        TransSignal_t   m_sig_transition;
        CEGUI::Window*  m_root;
        CEGUI::String   m_anim_exit;
        CEGUI::String   m_anim_enter;
        Game*           m_game;

    public:
        Screen();
        virtual ~Screen();

        CEGUI::Window*          get_root();
        const CEGUI::String&    get_anim_exit();
        const CEGUI::String&    get_anim_enter();
        TransSignal_t&          sig_transition();

        virtual void            set_game(Game* game);
        virtual void            exec();
};

#endif /* PAGE_H_ */
