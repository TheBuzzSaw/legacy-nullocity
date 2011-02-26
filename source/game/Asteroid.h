#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"
#include <GLee/GLee.h>


class Asteroid : public Entity
{
    public:

        ~Asteroid();
        Asteroid(vec2f pPosition);
        Asteroid(vec2f pPosition, float pRotation, vec2f pVelocity);

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix);

    protected:
    private:
        float* mPts;
        int* mInd;
        Asteroid();

        float mFieldDepth;
        float mScale;
};

#endif // ASTEROID_H
