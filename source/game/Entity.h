#ifndef ENTITY_H
#define ENTITY_H

#include <CGE/Graphics.h>
#include <CGE/Matrix4x4.h>
#include <CGE/Vectors.h>
#include <iostream>
using namespace std;

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        virtual void render(const CGE::Matrix4x4<GLfloat>& inMatrix) = 0;
        virtual void onPulse();
        virtual void onDeath(); // when HP hit zero
        virtual void onCollision();

        static void collide(Entity& objectOne, Entity& objectTwo);

        inline float getRadius() { return mRadius; }
        inline float getPosX() { return mPosition[0]; }
        inline float getPosY() { return mPosition[1]; }
//        inline bool isDead() { return !mHP && mMaxHP; }

        void applyForce(vec2f inAcceleration, float inMass);
        void applyAcceleration(vec2f inAcceleration);

    protected:
        vec2f mPosition;

        /// momentum
        vec2f mVelocity;
        float mMass;

        float mRotation; // Z-rotation
        float mRadius; // "size" of object

  //      unsigned int mHP;
  //      unsigned int mMaxHP;

    private:

        Entity(const Entity& inEntity)
        {
            // no copying
        }

        Entity& operator=(const Entity& inEntity)
        {
            // no copying
            return *this;
        }
};

#endif
