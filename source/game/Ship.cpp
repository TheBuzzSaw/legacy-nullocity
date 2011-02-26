#include "Ship.h"

Ship::Ship()
{
    mPts = new float[30]{
        //top
         0.0f, 1.0f,0.25f,  //0 front
         1.0f,-0.5f,0.25f,  //1 right
         1.0f,-1.0f,0.25f,  //2 rear right
        -1.0f,-1.0f,0.25f,  //3 rear left
        -1.0f,-0.5f,0.25f,  //4 left
        //bottom
         0.0f, 1.0f,-0.25f, //5 front
         1.0f,-0.5f,-0.25f, //6 right
         1.0f,-1.0f,-0.25f, //7 rear right
        -1.0f,-1.0f,-0.25f, //8 rear left
        -1.0f,-0.5f,-0.25f};//9 left

    mInd = new int[48]{
         0,1,2,0,2,3,0,3,4, //top
         5,7,6,5,8,7,5,9,8, //bottom
         3,2,8,2,7,8,       //back
         4,3,8,4,8,9,       //left
         2,1,6,2,6,7,       //right
         0,4,9,0,9,5,       //frontleft
         1,0,6,0,5,6        //right
         };

    mMass = 5.0f;
    mRotation = 90.0f;

    mStrafe = 0.0f;
    mThrust = 0.0f;
    mTurn = 0.0f;

    mMaxForwardThrust = 0.005f;
    mMaxReverseThrust = 0.003f;
    mMaxStrafeThrust = 0.003f;
    mMaxTurnSpeed = 2.0f;

    mRoll = 0;
    mDeltaRoll = 2;

    weaponSound.load("data/audio/dwang.ogg");

    mFieldDepth = -60.0f;
}

Ship::Ship(float pFieldDepth)
{
    mPts = new float[30]{
        //top
         0.0f, 1.0f,0.25f,  //0 front
         1.0f,-0.5f,0.25f,  //1 right
         1.0f,-1.0f,0.25f,  //2 rear right
        -1.0f,-1.0f,0.25f,  //3 rear left
        -1.0f,-0.5f,0.25f,  //4 left
        //bottom
         0.0f, 1.0f,-0.25f, //5 front
         1.0f,-0.5f,-0.25f, //6 right
         1.0f,-1.0f,-0.25f, //7 rear right
        -1.0f,-1.0f,-0.25f, //8 rear left
        -1.0f,-0.5f,-0.25f};//9 left

    mInd = new int[48]{
         0,1,2,0,2,3,0,3,4, //top
         5,7,6,5,8,7,5,9,8, //bottom
         3,2,8,2,7,8,       //back
         4,3,8,4,8,9,       //left
         2,1,6,2,6,7,       //right
         0,4,9,0,9,5,       //frontleft
         1,0,6,0,5,6//right
         };


    mMass = 5.0f;
    mRotation = 90.0f;

    mStrafe = 0.0f;
    mThrust = 0.0f;
    mTurn = 0.0f;

    mMaxForwardThrust = 0.005f;
    mMaxReverseThrust = 0.003f;
    mMaxStrafeThrust = 0.003f;
    mMaxTurnSpeed = 2.0f;

    mPosition[0] = 0;
    mPosition[1] = 0;

    mVelocity[0] = 0;
    mVelocity[1] = 0;

    mDeltaRoll = 2;
    mFieldDepth = pFieldDepth;
    mRoll = 0;
    mScale = 1;
}

Ship::~Ship()
{
    delete mPts;
    delete mInd;

    mPts = NULL;
    mInd = NULL;
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

void Ship::onDeath()
{
    //Nothing yet
}

void Ship::onCollision(const Entity& inEntity)
{
    //Nothing yet
}

void Ship::render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(mPosition[0],mPosition[1],mFieldDepth);
	glTranslatef(0,0,0); //ctr
	glRotatef(mRotation-90,0,0,1);
	glRotatef(mRoll,0,1,0);
	glScalef(mScale,mScale,mScale);
	glTranslatef(0,0,0);//-ctr

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 48; i++)
        {
            if (i == 0)
                glColor3f(1.0f,0.0f,0.0f);
            else if (i == 18)
                glColor3f(0.7f,0.7f,1.0f);
            else if (i == 24)
                glColor3f(0.0f,0.0f,1.0f);

            glVertex3f(mPts[mInd[i]*3],mPts[mInd[i]*3+1],mPts[mInd[i]*3+2]);
        }
    glEnd();
    glPopMatrix();
}

void Ship::fire()
{
    //Ima firin mah Lazer!!!!!
    weaponSound.play();
}
