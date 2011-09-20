#include "Entity.h"

Entity::Entity() : mMass(0.0f), mRotation(0.0f), mRadius(0.0f)
{
    mPosition[0] = 0.0f;
    mPosition[1] = 0.0f;

    mVelocity[0] = 0.0f;
    mVelocity[1] = 0.0f;
}

Entity::~Entity()
{
}



void Entity::display(const CGE::Matrix4x4<GLfloat>& inMatrix)
{
    CGE::Matrix4x4<GLfloat> matrix(inMatrix);
    matrix.translate(mPosition[0], mPosition[1], 0.0f);
    matrix.rotateZ(mRotation - 90.0f);
    matrix.rotateY(mRoll);
    matrix.scale(mScale);
    glLoadMatrixf(matrix);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    mVertexVBO.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);

    mColorVBO.bind();
    glColorPointer(4, GL_FLOAT, 0, 0);

    mIVBO.draw();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Entity::onPulse()
{
    mPosition[0] += mVelocity[0];
    mPosition[1] += mVelocity[1];

//    if (mMaxHP && !mHP)
//    {
//        onDeath();
//    }
}

void Entity::onDeath()
{
    cout << "Entity Dead\n";
    cout.flush();
}

void Entity::onCollision()
{
    //do damage based on mass and velocity
    //if (mMaxHP && ! mHP)
    //    mHP--; //test code, remove when ready
}

void Entity::collide(Entity& objectOne, Entity& objectTwo)
{
    float a = objectTwo.mPosition[0] - objectOne.mPosition[0];
    float b = objectTwo.mPosition[1] - objectOne.mPosition[1];

    float d = sqrt(a * a + b * b);
    float nx = (objectTwo.mPosition[0] - objectOne.mPosition[0]) / d;
    float ny = (objectTwo.mPosition[1] - objectOne.mPosition[1]) / d;

    float p = 2 * (objectOne.mVelocity[0] * nx + objectOne.mVelocity[1] * ny
                 - objectTwo.mVelocity[0] * nx - objectTwo.mVelocity[1] * ny)
                / (objectOne.mMass + objectTwo.mMass);

    objectOne.mVelocity[0] -= p * objectTwo.mMass * nx;
    objectOne.mVelocity[1] -= p * objectTwo.mMass * ny;
    objectOne.onCollision();

    objectTwo.mVelocity[0] += p * objectOne.mMass * nx;
    objectTwo.mVelocity[1] += p * objectOne.mMass * ny;
    objectTwo.onCollision();
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
