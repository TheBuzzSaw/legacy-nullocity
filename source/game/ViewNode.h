#ifndef VIEWNODE_H
#define VIEWNODE_H

#include <CGE/Vectors.h>

#include "SceneGraphNode.h"

class ViewNode : public SceneGraphNode
{
    public:
        ViewNode();
        virtual ~ViewNode();

        void setProjection(const CGE::Matrix4x4<float>& inProjection);
        void update();
        void updateAllMatrices();

        void setDistance(float inDistance);
        void changeDistance(float inOffset);
        void setRotation(float inRotation);
        void changeRotation(float inOffset);
        void setAngle(float inAngle);
        void changeAngle(float inOffset);
        void setPosition(float inX, float inY, float inZ);
        void changePosition(float inX, float inY, float inZ);
        void smartPan(float inX, float inY);

    protected:
    private:
        CGE::Matrix4x4<float> mProjection;
        CGE::Matrix4x4<float> mView;
        vec3f mPosition;
        float mDistance;
        float mRotation;
        float mAngle;
};

#endif
