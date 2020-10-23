//
//  OpenGLESHelper.cpp
//  testios
//
//  Created by chenyue on 2020/10/22.
//  Copyright © 2020 chenyue. All rights reserved.
//

#include "OpenGLESHelper.hpp"
#include <assert.h>
#include <stdio.h>

#define MAX_LOG_LENGTH  128

namespace OpenGLESHelper {
void outputCompileShader(GLuint shader)
{
    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (GL_FALSE == status)
    {
        GLint len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        if (len < MAX_LOG_LENGTH)
        {
            GLchar szBuf[MAX_LOG_LENGTH + 1] = { 0 };
            glGetShaderInfoLog(shader, MAX_LOG_LENGTH, nullptr, szBuf);
            printf("%s\n", szBuf);
        }
        else
        {
            GLchar *buf = new GLchar[len + 1];
            glGetShaderInfoLog(shader, len, nullptr, buf);
            buf[len] = '\0';
            printf("%s\n", buf);
            delete[]buf;
        }
        assert(GL_FALSE != status);
    }
}

GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len) {
    GLenum ret = GL_NO_ERROR;
    GLuint shader = 0;

    do
    {
        if (0 == (shader = glCreateShader(type))) {
            ret = glGetError();
            assert(false);
            break;
        }
        GLint lens[] = { len };
        glShaderSource(shader, 1, &source, (len > 0 ? lens : nullptr)); CHECK_BREAK;
        glCompileShader(shader);
        outputCompileShader(shader); CHECK_BREAK;
        glAttachShader(program, shader); CHECK_BREAK;
    } while (false);

    if (0 != shader) {
        glDeleteShader(shader);
        shader = 0;
    }
    return ret;
}
}
