//
//  OpenGLESHelper.hpp
//  testios
//
//  Created by chenyue on 2020/10/22.
//  Copyright © 2020 chenyue. All rights reserved.
//

#ifndef OpenGLESHelper_hpp
#define OpenGLESHelper_hpp

#include <stdio.h>
#include <assert.h>
#include <OpenGLES/ES3/glext.h>

inline void CHECKERR() {
    int err = 0;
    if (GL_NO_ERROR != (err = glGetError())){
        assert(false);
        printf("glGetError=%d\n", err);
    }
}

#define BUFFER_OFFSET(offset) ((void*)(offset))

#define CHECK_BREAK \
    if (GL_NO_ERROR != (ret = glGetError())) { \
        printf("glGetError=%x\n", ret); \
        assert(false); \
        break; \
    }

namespace OpenGLESHelper{
GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len);
};
#endif /* OpenGLESHelper_hpp */
