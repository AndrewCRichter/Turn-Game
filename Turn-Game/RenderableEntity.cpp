#include "RenderableEntity.h"



RenderableEntity::RenderableEntity()
{
}


RenderableEntity::~RenderableEntity()
{
}

float RenderableEntity::getDepth(int x, int z, Direction dir)
{
    int xz[2];
    getXZ(xz);
    int inPlane[2], depthDir[2];
    inPlane[0] = DIRECTION_VALUES[dir][0];
    inPlane[1] = DIRECTION_VALUES[dir][1];
    depthDir[0] = DIRECTION_VALUES[(dir + 1) % 6][0];
    depthDir[1] = DIRECTION_VALUES[(dir + 1) % 6][1];
    int inpl, dpth;
    if (inPlane[0] == 0) {
        inpl = xz[1] * inPlane[1];
        dpth = xz[0] * depthDir[0];
    }
    else if (inPlane[1] == 0) {
        inpl = xz[0] * inPlane[0];
        dpth = xz[0] * inPlane[0] * depthDir[1];
    
    }
    else {
            inpl = xz[0] * inPlane[0];
            dpth = xz[0] * inPlane[0] * depthDir[1];
    }

    return dpth;
}
