#include "ViewNode.h"
#include <CGE/Tools.h>

ViewNode::ViewNode() : mDistance(0.0f), mRotation(0.0f), mAngle(0.0f)
{
}

ViewNode::~ViewNode()
{
}

void ViewNode::setProjection(const CGE::Matrix4x4<float>& inProjection)
{
    mProjection = inProjection;
}

void ViewNode::update()
{
    mView.loadIdentity();
    if (mDistance > 0.0f) mView.translate(0.0f, 0.0f, -mDistance);
    mView.rotateX(mAngle);
    mView.rotateZ(mRotation);
    mView.translate(-mPosition[0], -mPosition[1], -mPosition[2]);
    mTransform = mView;
}

void ViewNode::updateAllMatrices()
{
    updateMatrices(mProjection);
}

void ViewNode::setDistance(float inDistance)
{
    if (inDistance < 0.0f)
        mDistance = 0.0f;
    else
        mDistance = inDistance;
}

void ViewNode::changeDistance(float inOffset)
{
    setDistance(mDistance + inOffset);
}

void ViewNode::setRotation(float inRotation)
{
    if (inRotation < 0.0f)
        mRotation = fmod(inRotation - 180.0f, 360.0f) + 180.0f;
    else
        mRotation = fmod(inRotation + 180.0f, 360.0f) - 180.0f;
}

void ViewNode::changeRotation(float inOffset)
{
    setRotation(mRotation + inOffset);
}

void ViewNode::setAngle(float inAngle)
{
    if (inAngle < 0.0f)
        mAngle = fmod(inAngle - 180.0f, 360.0f) + 180.0f;
    else
        mAngle = fmod(inAngle + 180.0f, 360.0f) - 180.0f;
}

void ViewNode::changeAngle(float inOffset)
{
    setAngle(mAngle + inOffset);
}

void ViewNode::setPosition(float inX, float inY, float inZ)
{
    mPosition[0] = inX;
    mPosition[1] = inY;
    mPosition[2] = inZ;
}

void ViewNode::changePosition(float inX, float inY, float inZ)
{
    mPosition[0] = inX;
    mPosition[1] = inY;
    mPosition[2] = inZ;
}

void ViewNode::smartPan(float inX, float inY)
{
     float theta = TO_RADIANS(mRotation);
     float c = cos(theta);
     float s = sin(theta);
     float dxp = c * inX;
     float dyp = -s * inX;
     dxp += s * inY;
     dyp += c * inY;

     mPosition[0] += dxp;
     mPosition[1] += dyp;
}
