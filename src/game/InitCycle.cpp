/*
 *  \file   InitStep.cpp
 *
 *  \date   Apr 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */


#include "InitCycle.h"

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
    switch(outer)
    {
        case CLEAR_PATCHES:
        {
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
            outer++;
            sig_freeMeshes.emit();
            break;
        }

        case CREATE_MESHES:
        {
            outer++;
            sig_createMeshes.emit();
            break;
        }

        case INIT_PATCHES:
        {
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
            outer++;
            sig_initRun.emit();
            break;
        }

        case DONE:
        {
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
