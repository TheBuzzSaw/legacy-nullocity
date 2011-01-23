#include "Shader.h"
#include "Exception.h"

#include <cstdio>

namespace CGE
{
    const char* Shader::mFile = "(direct buffer)";

    Shader::Shader(GLenum inType) : mHandle(0), mType(inType)
    {
    }

    Shader::~Shader()
    {
        unload();
    }

    void Shader::loadFromFile(const char* inFile)
    {
        static const char* functionName = "Shader::loadFromFile";

        if (mHandle || !inFile || !*inFile) return;

        char* source = fileToBuffer(inFile);
        if (!source)
        {
            std::string message("failed to convert ");
            message += inFile;
            message += " to buffer";
            throw Exception(functionName, message);
        }

        const char* temp = mFile;
        mFile = inFile;
        loadFromBuffer(source);
        mFile = temp;

        delete [] source;
    }

    void Shader::loadFromBuffer(const char* inBuffer)
    {
        static const char* functionName = "Shader::loadFromBuffer";

        if (!mHandle) mHandle = glCreateShader(mType);

        if (!mHandle) throw Exception(functionName, "failed to create shader");

        glShaderSource(mHandle, 1, const_cast<const GLchar**>(&inBuffer), 0);
        glCompileShader(mHandle);

        GLint compiled;
        glGetShaderiv(mHandle, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLchar log[2048];
            GLsizei length;
            glGetShaderInfoLog(mHandle, 2048, &length, log);

            glDeleteShader(mHandle);
            mHandle = 0;

            std::string message("shader compiler errors -- ");
            message += mFile;
            message += '\n';
            message += log;

            throw Exception(functionName, message);
        }
    }

    void Shader::unload()
    {
        if (mHandle) glDeleteShader(mHandle);
    }

    char* Shader::fileToBuffer(const char* inFile)
    {
        FILE *f;
        size_t length;
        size_t r;
        char* outBuffer;

        if (!(f = fopen(inFile, "r"))) return NULL;

        fseek(f, 0, SEEK_END);
        length = ftell(f);

        fseek(f, 0, SEEK_SET);

        outBuffer = static_cast<char*>(malloc((length + 1) * sizeof(char)));
        if (!outBuffer) return NULL;

        r = fread(outBuffer, sizeof(char), length, f);
        outBuffer[length] = '\0';
        fclose(f);

        return outBuffer;
    }
}
