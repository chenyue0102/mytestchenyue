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
#include "My/OpenGLShaderProgram.h"
#include <vector>
#include <memory>
#include <functional>

#include <spine/spine.h>

class SpineItem;


struct Point
{
    Point(float _x, float _y) :x(_x), y(_y) {}
    Point(): x(0.0f), y(0.0f) {}
    GLfloat x;
    GLfloat y;
};

struct SpineVertex{
    float x, y;

    float u, v;

    spine::Color color;
};

struct RectF {
	RectF(float _x, float _y, float _w, float _h)
		: x(_x)
		, y(_y)
		, w(_w)
		, h(_h)
	{

	}
	RectF() {
		x = y = w = h = 1.0f;
	}
	float x, y, w, h;
	float left() { return x; }
	float right() { return x + w; }
	float top() { return y; }
	float bottom() { return y + h; }
	float width() { return w; }
	float height() { return h; }
};

class MyTexture;

//#define USE_QT_PROGRAM

#ifdef USE_QT_PROGRAM
#include <QOpenGLShaderProgram>
typedef QOpenGLShaderProgram MyOpenGLShaderProgram;
#else
typedef OpenGLShaderProgram MyOpenGLShaderProgram;
#endif
class RenderCmdsCache
{
public:
    explicit RenderCmdsCache(SpineItem* spItem = nullptr);
    ~RenderCmdsCache();

    enum ShaderType {
        ShaderTexture,
        ShaderColor
    };

    void clearCache();

    void blendFunc(GLenum sfactor, GLenum dfactor);
    void bindShader(ShaderType);
    void drawColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
    void lineWidth(GLfloat width);
    void pointSize(GLfloat pointSize);

    void drawTriangles(MyTexture *texture, std::vector<SpineVertex> vertices,
		std::vector<GLushort> triangles, const spine::Color& blendColor, const int &blendColorChannel, float light);
    void drawPoly(const Point* points, int pointCount);
    void drawLine(const Point& origin, const Point& destination);
    void drawPoint(const Point& point);

    void render();
    void setSkeletonRect(const RectF& rect);

    void initShaderProgram();

    bool isValid();

public:
	std::function<void()> cacheRendered;

private:
    std::vector<std::function<void()> > mglFuncs;
    RectF mRect;

    MyOpenGLShaderProgram* mTextureShaderProgram = nullptr;
    MyOpenGLShaderProgram* mColorShaderProgram = nullptr;
    bool m_shaderInited = false;
    SpineItem* m_spItem = nullptr;
};

#endif // POLYGONBATCH_H
