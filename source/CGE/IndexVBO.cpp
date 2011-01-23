#include "IndexVBO.h"

namespace CGE
{
    IndexVBO::IndexVBO() : mSize(0)
    {
        glGenBuffers(1, &mBuffer);
    }

    IndexVBO::~IndexVBO()
    {
        glDeleteBuffers(1, &mBuffer);
    }

    void IndexVBO::loadData(GLenum inMode, GLuint inSize, const GLuint* inData,
        GLenum inUsage)
    {
        mMode = inMode;
        mSize = inSize;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, inSize * sizeof(GLuint),
            inData, inUsage);
    }

    void IndexVBO::setMode(GLenum inMode)
    {
        mMode = inMode;
    }

    void IndexVBO::draw() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
        glDrawElements(mMode, mSize, GL_UNSIGNED_INT, 0);
    }
}
