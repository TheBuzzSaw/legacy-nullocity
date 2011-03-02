#include "Asteroid.h"

Asteroid::Asteroid()
{
}

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
         0.0f,  1.0f,  0.0f, //0 top
         1.0f, -1.0f,  0.0f, //1 right
        -1.0f, -1.0f, -1.0f, //2 left far
        -1.0f, -1.0f,  1.0f};//3 left near

    mVertexVBO.loadData(vertices, 4, 3);

    GLfloat indices[12]{
        1, 3, 0,  //front
        2, 1, 0,  //back
        2, 3, 0,  //left
        2, 1, 3}; //bottom

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

    glColor3f(139,69,19);


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
