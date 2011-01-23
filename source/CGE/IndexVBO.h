#ifndef INDEXVBO_H
#define INDEXVBO_H

#include "Graphics.h"

namespace CGE
{
    class IndexVBO
    {
        public:
            IndexVBO();
            ~IndexVBO();

            void draw() const;
            void loadData(GLenum inMode, GLuint inSize, const GLuint* inData,
                GLenum inUsage = GL_STATIC_DRAW);
            void setMode(GLenum inMode);

        private:
            GLenum mMode;
            GLuint mBuffer;
            GLuint mSize;
    };
}

#endif
