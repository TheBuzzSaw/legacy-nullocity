#ifndef BULLET_H
#define BULLET_H

#include <GLee/GLee.h>
#include <CGE/IndexVBO.h>
#include "Entity.h"

class Bullet : public Entity
{
    public:
        Bullet(vec2f pPosition);
        Bullet(vec2f pPosition, float pRotation, vec2f pVelocity);

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix);

    protected:
    private:

        Bullet();

        float mScale;

        CGE::VertexBufferObject mVertexVBO;
        CGE::IndexVBO mIVBO;
        CGE::VertexBufferObject mColorVBO;

};

#endif // BULLET_H
