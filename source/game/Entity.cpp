#include "Entity.h"

Entity::Entity() : mMass(0.0f), mRotation(0.0f), mRadius(0.0f), mHP(0),
    mMaxHP(0)
{
    mPosition[0] = 0.0f;
    mPosition[1] = 0.0f;

    mVelocity[0] = 0.0f;
    mVelocity[1] = 0.0f;
}

Entity::~Entity()
{
}

void Entity::onPulse()
{
    mPosition[0] += mVelocity[0];
    mPosition[1] += mVelocity[1];
}

void Entity::onDeath()
{
}

void Entity::onCollision(const Entity& inEntity)
{
    cout << "Collision!";
}

void Entity::applyForce(vec2f inAcceleration, float inMass)
{
    mVelocity[0] = (inAcceleration[0] * inMass + mVelocity[0] * mMass)
        / mMass;
    mVelocity[1] = (inAcceleration[1] * inMass + mVelocity[1] * mMass)
        / mMass;
}

void Entity::applyAcceleration(vec2f inAcceleration)
{
    mVelocity[0] += inAcceleration[0];
    mVelocity[1] += inAcceleration[1];
}
