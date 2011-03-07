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

void Entity::onCollision(Entity& inEntity, int recurse)
{
    cout << "Collision!";
    cout.flush();
    float a = inEntity.mPosition[0] - mPosition[0];
    float b = inEntity.mPosition[1] - mPosition[1];

    float d = sqrt(a * a + b * b);
    float nx = (inEntity.mPosition[0] - mPosition[0]) / d;
    float ny = (inEntity.mPosition[1] - mPosition[1]) / d;
    float n = sqrt(nx * nx + ny * ny);
    float p = 2 * (mVelocity[0] * nx + mVelocity[1] * ny - inEntity.mVelocity[0] * nx - inEntity.mVelocity[1] * ny) / (mMass + inEntity.mMass);

    if (recurse)
        inEntity.onCollision((*this), 0);

    mVelocity[0] = mVelocity[0] - p * inEntity.mMass * nx;
    mVelocity[1] = mVelocity[1] - p * inEntity.mMass * ny;

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
