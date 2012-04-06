/*
 *  \file   InitPhase.h
 *
 *  \date   Apr 5, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief
 */

#ifndef INITCYCLE_H_
#define INITCYCLE_H_

#include <cassert>
#include <sigc++/sigc++.h>

struct InitCycle
{
    private:
        enum OuterStep
        {
            CLEAR_PATCHES   =0,
            FREE_MESHES,
            CREATE_MESHES,
            INIT_PATCHES,
            DONE,
            NUM_STEPS
        };

        int     outer;
        int     nPatches;
        int     iPatch;

    public:
        sigc::signal<void,int> sig_clearPatch;
        sigc::signal<void,int> sig_initPatch;
        sigc::signal<void>     sig_freeMeshes;
        sigc::signal<void>     sig_createMeshes;
        sigc::signal<void>     sig_done;
        sigc::signal<void,float>    sig_progress;

    InitCycle();
    void setNumPatches(int nPatches);
    void reset();
    void step();
};



#endif
