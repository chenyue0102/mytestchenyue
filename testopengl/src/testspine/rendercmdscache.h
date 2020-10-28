/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 *
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef POLYGONBATCH_H
#define POLYGONBATCH_H

#include <vector>
#include <memory>
#include <functional>

#include <spine/spine.h>
#include "StructDefine.h"
#include "OpenGLShaderProgram.h"
#define USE_TRANSFORM_FEEDBACK
#ifdef USE_TRANSFORM_FEEDBACK
#include "TransformFeedback.h"
#endif

class SpineItem;
class MyTexture;
typedef OpenGLShaderProgram MyOpenGLShaderProgram;
class RenderCmdsCache
{
public:
    RenderCmdsCache();
    ~RenderCmdsCache();

public:
	void setSkeletonRect(const MyRect &rect);

	//初始化Shader
	void initShaderProgram();

	bool isValid();

	//绘制到窗口
	void render();

	void clearCache();

    enum ShaderType {
        ShaderTexture,
        ShaderColor
    };

    void blendFunc(GLenum sfactor, GLenum dfactor);
    void bindShader(ShaderType);
    void drawColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
    void lineWidth(GLfloat width);
    void pointSize(GLfloat pointSize);

    void drawTriangles(MyTexture *texture, std::vector<SpineVertex> vertices,
		std::vector<GLushort> triangles, const MyColor& blendColor, const int &blendColorChannel, float light);
    void drawPoly(const MyPoint* points, int pointCount);
    void drawLine(const MyPoint& origin, const MyPoint& destination);
    void drawPoint(const MyPoint& point);

private:
    std::vector<std::function<void()> > mglFuncs;
	MyRect mRect;

    MyOpenGLShaderProgram* mTextureShaderProgram = nullptr;
    MyOpenGLShaderProgram* mColorShaderProgram = nullptr;
#ifdef USE_TRANSFORM_FEEDBACK
	TransformFeedback *mTransformFeedback = nullptr;
#endif
    bool m_shaderInited = false;
};

#endif // POLYGONBATCH_H
