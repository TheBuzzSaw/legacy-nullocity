#ifndef GENERALPROGRAM_H
#define GENERALPROGRAM_H

#include <CGE/Program.h>
#include <CGE/VertexShader.h>
#include <CGE/FragmentShader.h>
#include <CGE/Matrix4x4.h>

class GeneralProgram : public CGE::Program<2>
{
    public:
        GeneralProgram();
        virtual ~GeneralProgram();

        void setMatrix(const CGE::Matrix4x4<GLfloat>& inMatrix);

    private:
        CGE::VertexShader mVS;
        CGE::FragmentShader mFS;

        GLuniform mUniMVPM;
        GLuniform mUniTexture;
};

#endif
