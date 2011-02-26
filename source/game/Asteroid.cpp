#include "Asteroid.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(vec2f pPosition)
{
    GLfloat vertices[12]{
         0.0f,  1.0f,  0.0f, //1 top
         1.0f, -1.0f,  0.0f, //2 right
        -1.0f, -1.0f, -1.0f, //3 left far
        -1.0f, -1.0f,  1.0f};//4 left near

    mVertexVBO.loadData(vertices, 4, 3);

    GLfloat indices[12]{
        2, 4, 1,  //front
        3, 2, 1,  //back
        3, 4, 1,  //left
        3, 2, 4}; //bottom

    mIVBO.loadData(indices, 12);

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
    GLfloat vertices[12]{
         0.0f,  1.0f,  0.0f, //1 top
         1.0f, -1.0f,  0.0f, //2 right
        -1.0f, -1.0f, -1.0f, //3 left far
        -1.0f, -1.0f,  1.0f};//4 left near

    mVertexVBO.loadData(vertices, 4, 3);

    GLfloat indices[12]{
        2, 4, 1,  //front
        3, 2, 1,  //back
        3, 4, 1,  //left
        3, 2, 4}; //bottom

    mIVBO.loadData(indices, 12);

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


    glEnableClientState(GL_VERTEX_ARRAY);

    mVertexVBO.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);

    mIVBO.draw();

    glDisableClientState(GL_VERTEX_ARRAY);
}
