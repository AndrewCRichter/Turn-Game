#include "RenderableEntity.h"

int * RenderableEntity::getXZ(int * xz)
{
    xz[0] = 0;
    xz[1] = 0;
    return xz;
}

float RenderableEntity::getY()
{
    return 0.0f;
}

int RenderableEntity::getXOffset()
{
    return 0;
}

Direction RenderableEntity::getDirection()
{
    return (Direction)0;
}

float RenderableEntity::getDepth(int x, int z, Direction dir, float* offset)
{
    int xz[2];
    this->getXZ(xz);
    int inPlane[2], depthDir[2];
    inPlane[0] = DIRECTION_VALUES[dir][0];
    inPlane[1] = DIRECTION_VALUES[dir][1];
    depthDir[0] = DIRECTION_VALUES[(dir + 1) % 6][0];
    depthDir[1] = DIRECTION_VALUES[(dir + 1) % 6][1];
    int inpl, dpth,
        orip,ordh;
    if (inPlane[0] == 0) {
        inpl = xz[1] * inPlane[1];
        dpth = xz[0] * depthDir[0];
        orip = z * inPlane[1];
        ordh = x * depthDir[0];
    }
    else if (inPlane[1] == 0) {
        inpl = xz[0] * inPlane[0];
        dpth = xz[0] - xz[0] * inPlane[0] * depthDir[1];
        inpl = x * inPlane[0];
        dpth = depthDir[0]*(z - x * inPlane[0] * depthDir[1]);
    }
    else {
        inpl = xz[0] * inPlane[0];
        dpth = xz[1] * inPlane[0];
        orip = x * inPlane[0];
        ordh = z * inPlane[0];
    }
    *offset = (float) -inpl + orip;

    return (float) (dpth - ordh);
}

void RenderableEntity::draw(sf::RenderTarget & rt, sf::RenderStates states) {}
