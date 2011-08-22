#ifndef ASTEROID_H
#define ASTEROID_H

#include <GLee/GLee.h>
#include <CGE/IndexVBO.h>
#include "Entity.h"

class Asteroid : public Entity
{
    public:

        ~Asteroid();
        Asteroid(vec2f pPosition);
        Asteroid(vec2f pPosition, float pRotation, vec2f pVelocity);

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix);

    protected:
    private:

        Asteroid();

        float mScale;

        CGE::VertexBufferObject mVertexVBO;
        CGE::IndexVBO mIVBO;
        CGE::VertexBufferObject mColorVBO;
};

#endif // ASTEROID_H
