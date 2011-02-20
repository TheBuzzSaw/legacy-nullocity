#ifndef ENTITY_H
#define ENTITY_H

#include <CGE/Vectors.h>

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        virtual void render() = 0;
        virtual void onPulse();
        virtual void onDeath(); // when HP hit zero
        virtual void onCollision(const Entity& inEntity);

        void applyForce(vec2f inAcceleration, float inMass);
        void applyAcceleration(vec2f inAcceleration);

    protected:
        vec2f mPosition;

        /// momentum
        vec2f mVelocity;
        float mMass;

        float mRotation; // Z-rotation
        float mRadius; // "size" of object

        unsigned int mHP;
        unsigned int mMaxHP;

    private:

        Entity(const Entity& inEntity)
        {

        }

        Entity& operator=(const Entity& inEntity)
        {
            // no copying
            return *this;
        }
};

#endif
