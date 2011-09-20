#include "Asteroid.h"

Asteroid::Asteroid(vec2f pPosition)
{
    GLfloat vertices[12] = {
         0.0f,  1.0f,  0.0f, //0 top
         1.0f, -1.0f,  0.0f, //1 right
        -1.0f, -1.0f, -1.0f, //2 left far
        -1.0f, -1.0f,  1.0f};//3 left near

    mVertexVBO.loadData(vertices, 4, 3);

    GLuint indices[12] = {
        1, 3, 0,  //front
        2, 1, 0,  //back
        2, 3, 0,  //left
        2, 1, 3}; //bottom

    mIVBO.loadData(indices, 12);

    GLfloat colors[16] = {
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f};

    mColorVBO.loadData(colors,4,4);

    mPosition[0] = pPosition[0];
    mPosition[1] = pPosition[1];
    mRotation = 0.0f;
    mVelocity[0] = 0.0f;
    mVelocity[1] = 0.0f;
    mRadius = 1.0f;
    mMass = 10.0f;

    mScale = 1.0f;
}

Asteroid::Asteroid(vec2f pPosition, float pRotation, vec2f pVelocity)
{
    GLfloat vertices[12] = {
         0.0f,  1.0f,  0.0f, //0 top
         1.0f, -1.0f,  0.0f, //1 right
        -1.0f, -1.0f, -1.0f, //2 left far
        -1.0f, -1.0f,  1.0f };//3 left near

    mVertexVBO.loadData(vertices, 4, 3);

    GLfloat indices[12] = {
        1, 3, 0,  //front
        2, 1, 0,  //back
        2, 3, 0,  //left
        2, 1, 3 }; //bottom

    mIVBO.loadData(indices, 12);

    GLfloat colors[16] = {
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f,
        0.54f, 0.27f, 0.07f, 1.0f };

    mColorVBO.loadData(colors,4,4);

    mPosition[0] = pPosition[0];
    mPosition[1] = pPosition[1];
    mRotation = pRotation;
    mVelocity[0] = pVelocity[0];
    mVelocity[1] = pVelocity[1];
    mRadius = 1.0f;
    mMass = 10.0f;

    mScale = 1.0f;
}
Asteroid::~Asteroid()
{

}

