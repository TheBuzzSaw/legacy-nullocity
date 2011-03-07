#include "Ship.h"

Ship::Ship(float pFieldDepth) : mFieldDepth(pFieldDepth)
{
    GLfloat vertices[30] = {
        //top
         0.0f,  1.0f, 0.25f,  //0 front
         1.0f, -0.5f, 0.25f,  //1 right
         1.0f, -1.0f, 0.25f,  //2 rear right
        -1.0f, -1.0f, 0.25f,  //3 rear left
        -1.0f, -0.5f, 0.25f,  //4 left
        //bottom
         0.0f,  1.0f, -0.25f, //5 front
         1.0f, -0.5f, -0.25f, //6 right
         1.0f, -1.0f, -0.25f, //7 rear right
        -1.0f, -1.0f, -0.25f, //8 rear left
        -1.0f, -0.5f, -0.25f  //9 left
        };

    mVertexVBO.loadData(vertices, 10, 3);

    GLuint indices[48] = {
         0, 1, 2, 0, 2, 3, 0, 3, 4, //top
         5, 7, 6, 5, 8, 7, 5, 9, 8, //bottom
         3, 2, 8, 2, 7, 8,          //back
         4, 3, 8, 4, 8, 9,          //left
         2, 1, 6, 2, 6, 7,          //right
         0, 4, 9, 0, 9, 5,          //frontleft
         1, 0, 6, 0, 5, 6           //right
         };

    mIVBO.loadData(indices, 48);


    GLfloat colors[40] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f};

    mColorVBO.loadData(colors, 10, 4);

    mMass = 1.0f;
    mRotation = 90.0f;

    mStrafe = 0.0f;
    mThrust = 0.0f;
    mTurn = 0.0f;

    mMaxForwardThrust = 0.05f;
    mMaxReverseThrust = 0.03f;
    mMaxStrafeThrust = 0.03f;
    mMaxTurnSpeed = 2.0f;

    mPosition[0] = 0;
    mPosition[1] = 0;

    mVelocity[0] = 0;
    mVelocity[1] = 0;

    mRadius = 1.0f;

    mDeltaRoll = 2;
    mRoll = 0;
    mScale = 1;
}

Ship::~Ship()
{
}

void Ship::setStrafe(float strafeInput)
{
    mStrafe = strafeInput * mMaxStrafeThrust;
}

void Ship::setThrust(float thrustInput)
{
    if (thrustInput < 0)
        mThrust = thrustInput * mMaxForwardThrust;
    else
        mThrust = thrustInput * mMaxReverseThrust;
}

void Ship::setTurn(float turnInput)
{
    mTurn = turnInput * mMaxTurnSpeed;
}


void Ship::rollRight()
{
    if (mRoll < 90)
        mRoll += mDeltaRoll;
}

void Ship::rollLeft()
{
    if (mRoll > -90)
        mRoll -= mDeltaRoll;
}

void Ship::rollReset()
{
    if (mRoll > 0)
        mRoll -=mDeltaRoll;
    if (mRoll < 0)
        mRoll +=mDeltaRoll;
}

void Ship::onPulse()
{
    mRotation += mTurn;
    mForce[0] = mThrust * cos(mRotation * M_PI/180.0f) + mStrafe * sin(-mRotation * M_PI/180.0f);
    mForce[1] = mThrust * sin(mRotation * M_PI/180.0f) + mStrafe * cos(-mRotation * M_PI/180.0f);
    applyForce(mForce,0.5f);

    if (mThrust > 0)
    {
        if (mTurn > 0)
            rollLeft();
        else if (mTurn < 0)
            rollRight();
        else
            rollReset();
    }
    else
        rollReset();
    Entity::onPulse();
}

void Ship::render(const CGE::Matrix4x4<GLfloat>& inMatrix)
{
    CGE::Matrix4x4<GLfloat> matrix(inMatrix);
    matrix.translate(mPosition[0], mPosition[1], mFieldDepth);
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

void Ship::fire()
{
    cout << "Ima firin mah Lazer!!!!!";
    weaponSound.play();
}
