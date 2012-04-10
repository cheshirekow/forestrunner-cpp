/*
 *  \file   InitStep.cpp
 *
 *  \date   Apr 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */


#include "InitCycle.h"
#include <iostream>

InitCycle::InitCycle():
        outer(CREATE_MESHES),
        nPatches(0),
        iPatch(0)
{

}

void InitCycle::setNumPatches(int nPatches)
{
    this->nPatches = nPatches;
}

void InitCycle::reset()
{
    outer = CLEAR_PATCHES;
    iPatch= 0;
}

void InitCycle::step()
{
    std::cerr << "InitCycle::step : stepping through\n   ";
    switch(outer)
    {
        case CLEAR_PATCHES:
        {
            std::cerr << "CLEAR_PATCHES" << std::endl;
            if(++iPatch >= nPatches)
            {
                iPatch = 0;
                outer++;
            }
            sig_clearPatch.emit(iPatch);
            break;
        }

        case FREE_MESHES:
        {
            std::cerr << "FREE_MESHES" << std::endl;
            outer++;
            sig_freeMeshes.emit();
            break;
        }

        case CREATE_MESHES:
        {
            std::cerr << "CREATE_MESHES" << std::endl;
            outer++;
            sig_createMeshes.emit();
            break;
        }

        case INIT_PATCHES:
        {
            std::cerr << "INIT_PATCHES" << std::endl;
            if(++iPatch >= nPatches)
            {
                iPatch=0;
                outer++;
            }
            sig_initPatch.emit(iPatch);
            break;
        }

        case INIT_RUN:
        {
            std::cerr << "INIT_RUN" << std::endl;
            outer++;
            sig_initRun.emit();
            break;
        }

        case DONE:
        {
            std::cerr << "DONE" << std::endl;
            outer++;
            sig_done.emit();
            break;
        }

        default:
        {
            assert(false);
            break;
        }
    }

    sig_progress.emit(  (outer / (float)NUM_STEPS)
                            + (iPatch / (float)nPatches) );
}
