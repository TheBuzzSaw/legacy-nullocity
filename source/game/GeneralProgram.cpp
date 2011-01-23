#include "GeneralProgram.h"

GeneralProgram::GeneralProgram()
{
    mVS.loadFromFile("data/shaders/general.vs");
    mFS.loadFromFile("data/shaders/general.fs");
    attachShader(mVS);
    attachShader(mFS);
    bindAttribLocation(0, "iVertex");
    bindAttribLocation(1, "iTexture");
    link();
    mUniMVPM = getUniformLocation("uMVPM");
    mUniTexture = getUniformLocation("uTexture");

    glUniform1i(mUniTexture, 0);
}

GeneralProgram::~GeneralProgram()
{
}

void GeneralProgram::setMatrix(const CGE::Matrix4x4<GLfloat>& inMatrix)
{
    glUniformMatrix4fv(mUniMVPM, 1, GL_FALSE, inMatrix);
}
