#include "Asteroid.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(vec2f pPosition)
{
    mPts = new float[12] { 0, 1, 0, //top
                           1,-1, 0, //right
                          -1,-1,-1, //left far
                          -1,-1, 1};//left near

    mInd = new int[12] {2,4,1,  //front
                        3,2,1,  //back
                        3,4,1,  //left
                        3,2,4}; //bottom

    mPosition[0] = pPosition[0];
    mPosition[1] = pPosition[1];
    mRotation = 0.0f;
    mVelocity[0] = 0.0f;
    mVelocity[1] = 0.0f;

    mScale = 1.0f;

    mFieldDepth = -60;//remove after a camera is made
}

Asteroid::Asteroid(vec2f pPosition, float pRotation, vec2f pVelocity)
{
    mPts = new float[12] { 0, 1, 0, //top
                           1,-1, 0, //right
                          -1,-1,-1, //left far
                          -1,-1, 1};//left near

    mInd = new int[12] {1,4,2,  //front
                        3,2,1,  //back
                        3,4,1,  //left
                        3,2,4}; //bottom

    mPosition[0] = pPosition[0];
    mPosition[1] = pPosition[1];
    mRotation = pRotation;
    mVelocity[0] = pVelocity[0];
    mVelocity[1] = pVelocity[1];

    mScale = 1.0f;

    mFieldDepth = -60;//remove after a camera is made
}
Asteroid::~Asteroid()
{

}

void Asteroid::render(const CGE::Matrix4x4<GLfloat>& inMatrix)
{
    CGE::Matrix4x4<GLfloat> matrix(inMatrix);
    matrix.translate(mPosition[0], mPosition[1], mFieldDepth);
    matrix.rotateZ(mRotation - 90.0f);
    matrix.scale(mScale);
    glLoadMatrixf(matrix);

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 12; i++)
        {
            if (i == 0)
                glColor3f(0.54f,0.27f,0.07f);
            glVertex3f(mPts[mInd[i]*3],mPts[mInd[i]*3+1],mPts[mInd[i]*3+2]);
        }
    glEnd();
}
