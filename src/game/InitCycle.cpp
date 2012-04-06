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
            sig_clearPatch.emit(iPatch);
            if(++iPatch >= nPatches)
            {
                iPatch = 0;
                outer++;
            }
            break;
        }

        case FREE_MESHES:
        {
            sig_freeMeshes.emit();
            outer++;
            break;
        }

        case CREATE_MESHES:
        {
            sig_createMeshes.emit();
            outer++;
            break;
        }

        case INIT_PATCHES:
        {
            sig_initPatch.emit(iPatch);
            if(++iPatch >= nPatches)
            {
                iPatch=0;
                outer++;
            }
            break;
        }

        case DONE:
        {
            sig_done.emit();
            outer++;
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
