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

#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "vmath.h"

#include "rendercmdscache.h"
#include "My/MyTexture.h"

#include "spineitem.h"



class BlendFunction
{
public:
    explicit BlendFunction(GLenum sfactor, GLenum dfactor):msfactor(sfactor), mdfactor(dfactor){}
    virtual ~BlendFunction(){}

    virtual void invoke(){
        if (msfactor == GL_ONE && mdfactor == GL_ZERO){
			glDisable(GL_BLEND);
        }
        else
        {
			glEnable(GL_BLEND);
			glBlendFunc(msfactor, mdfactor);
        }
    }

private:
    GLenum msfactor;
    GLenum mdfactor;
};

class BindShader
{
public:
    explicit BindShader(MyOpenGLShaderProgram* program, const RectF& rect):mShaderProgram(program), mRect(rect){}
    virtual ~BindShader(){}

    virtual void invoke(){
#ifdef USE_QT_PROGRAM
		QMatrix4x4 matrix;
		matrix.ortho(mRect.left(), mRect.right(), mRect.bottom(), mRect.top(), -1, 1);
#else
		vmath::mat4 matrix = vmath::ortho(mRect.left(), mRect.right(), mRect.bottom(), mRect.top(), -1, 1);
#endif

        mShaderProgram->bind();
        mShaderProgram->setUniformValue("u_matrix", matrix);

        if (mShaderProgram->attributeLocation("a_position") != -1)
            mShaderProgram->enableAttributeArray("a_position");

        if (mShaderProgram->attributeLocation("a_color") != -1)
            mShaderProgram->enableAttributeArray("a_color");

        if (mShaderProgram->attributeLocation("a_texCoord") != -1)
            mShaderProgram->enableAttributeArray("a_texCoord");
    }

private:
	MyOpenGLShaderProgram* mShaderProgram;
    RectF  mRect;
};

class DrawColor
{
public:
    explicit DrawColor(MyOpenGLShaderProgram* program, const spine::Color& color):mShaderProgram(program), mColor(color){}
    virtual ~DrawColor(){}

    virtual void invoke(){
        if (mShaderProgram->uniformLocation("u_color") != -1)
			mShaderProgram->setUniformValue("u_color", mColor.r, mColor.g, mColor.b, mColor.a);
    }

private:
    MyOpenGLShaderProgram* mShaderProgram;
    spine::Color mColor;
};

class LineWidth
{
public:
    explicit LineWidth(GLfloat width):mWidth(width){}
    virtual ~LineWidth(){}

    virtual void invoke(){
		glLineWidth(mWidth);
    }

private:
    GLfloat mWidth;
};

class PointSize
{
public:
    explicit PointSize(GLfloat size):m_size(size){}
    virtual ~PointSize(){}

    virtual void invoke(){
#if defined(Q_OS_OSX)
        glPointSize(m_size);
#elif defined(Q_OS_WIN) && defined(Q_CC_MINGW)
        glPointSize(m_size);
#endif
    }

private:
    GLfloat m_size;
};

class MyTexture;
class DrawTrigngles
{
public:
    explicit DrawTrigngles(MyOpenGLShaderProgram* program,
                           MyTexture *texture,
                           spine::Vector<SpineVertex> vertices,
                           spine::Vector<GLushort> triangles,
                           spine::Color blendColor,
                           int blendColorChannel,
                           float light)
        :mShaderProgram(program)
        ,mTexture(texture)
        ,m_blendColor(blendColor)
        ,m_blendColorChannel(blendColorChannel)
        ,m_light(light)
    {
        auto numvertices = vertices.size();
        if (triangles.size() <= 0 || numvertices <= 0 || !triangles.buffer())
            return;
        m_vertices.setSize(numvertices, SpineVertex());
        memcpy((float*)m_vertices.buffer(), (float*)vertices.buffer(), sizeof (SpineVertex) * numvertices);
        m_triangles.setSize(triangles.size(), 0);
        memcpy(m_triangles.buffer(), triangles.buffer(), sizeof(GLushort)*triangles.size());
    }

    virtual ~DrawTrigngles()
    {
    }

    virtual void invoke()
    {
		if (0 != mTexture) {
#ifdef USE_QT_PROGRAM
			mTexture->bind(mShaderProgram->programId());
#else
			mTexture->bind(mShaderProgram->programId());
#endif
		}

        mShaderProgram->setAttributeArray("a_position", GL_FLOAT, &m_vertices[0].x, 2, sizeof(SpineVertex));
        mShaderProgram->setAttributeArray("a_color", GL_FLOAT, &m_vertices[0].color.r, 4, sizeof(SpineVertex));
        mShaderProgram->setAttributeArray("a_texCoord", GL_FLOAT, &m_vertices[0].u, 2, sizeof(SpineVertex));
        mShaderProgram->setUniformValue("u_blendColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, m_blendColor.a);
        mShaderProgram->setUniformValue("u_blendColorChannel", m_blendColorChannel);
        mShaderProgram->setUniformValue("u_light", m_light);
		glDrawElements(GL_TRIANGLES, m_triangles.size(), GL_UNSIGNED_SHORT, m_triangles.buffer());
    }

private:
    MyOpenGLShaderProgram* mShaderProgram;
    spine::Vector<SpineVertex> m_vertices;
    spine::Vector<GLushort> m_triangles;
    MyTexture *mTexture;
    spine::Color m_blendColor = spine::Color(255, 255, 255, 255);
    GLint m_blendColorChannel = -1;
    float m_light = 1.0;
};

class DrawPolygon
{
public:
    explicit DrawPolygon(MyOpenGLShaderProgram* program, const Point* points, int pointsCount)
        :mShaderProgram(program)
    {
        if (pointsCount <= 0 || !points)
            return;

        m_points.setSize(pointsCount, Point());
        memcpy(m_points.buffer(), points, sizeof(Point)*pointsCount);
    }

    virtual ~DrawPolygon()
    {
        if(m_points.size() > 0)
            m_points.setSize(0, Point());
    }

    virtual void invoke()
    {
        mShaderProgram->setAttributeArray("a_position", GL_FLOAT, m_points.buffer(), 2, sizeof(Point));
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) m_points.size());
    }

private:
    MyOpenGLShaderProgram* mShaderProgram;
    spine::Vector<Point> m_points;
};

class DrawLine
{
public:
    explicit DrawLine(MyOpenGLShaderProgram* program, const Point& origin, const Point& destination)
        :mShaderProgram(program)
    {
        mPoints[0] = origin;
        mPoints[1] = destination;
    }

    virtual ~DrawLine(){}

    virtual void invoke()
    {
        mShaderProgram->setAttributeArray("a_position", GL_FLOAT, mPoints, 2, sizeof(Point));
        glDrawArrays(GL_LINES, 0, 2);
    }

private:
    MyOpenGLShaderProgram* mShaderProgram;
    Point mPoints[2];
};

class DrawPoint
{
public:
    explicit DrawPoint(MyOpenGLShaderProgram* program, const Point& point)
        :mShaderProgram(program)
        ,mPoint(point)
    {}

    virtual ~DrawPoint(){}

    virtual void invoke()
    {
        mShaderProgram->setAttributeArray("a_position", GL_FLOAT, &mPoint, 2, sizeof(Point));
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    MyOpenGLShaderProgram* mShaderProgram;
    Point mPoint;
};

RenderCmdsCache::RenderCmdsCache(SpineItem* spItem)
    : m_spItem(spItem)
{
}

RenderCmdsCache::~RenderCmdsCache()
{
    clearCache();
    if(mTextureShaderProgram)
        delete mTextureShaderProgram;
    if(mColorShaderProgram)
        delete mColorShaderProgram;
    mTextureShaderProgram = nullptr;
    mColorShaderProgram = nullptr;
}

void RenderCmdsCache::clearCache()
{
    if (mglFuncs.empty())
        return;

    for (auto &func : mglFuncs)
		func();

    mglFuncs.clear();
}

void RenderCmdsCache::drawTriangles(MyTexture *texture, spine::Vector<SpineVertex> vertices,
                                    spine::Vector<GLushort> triangles, const spine::Color& blendColor,
                                    const int& blendColorChannel, float light)
{
	//todo
	auto fun = [texture, this, vertices, triangles, blendColor, blendColorChannel, light]() {
		DrawTrigngles draw(mTextureShaderProgram, texture,
			vertices, triangles, blendColor,
			blendColorChannel, light);
		draw.invoke();
	};
    mglFuncs.push_back(fun);
}

void RenderCmdsCache::blendFunc(GLenum sfactor, GLenum dfactor)
{
	auto fun = [sfactor, dfactor]() {
		BlendFunction draw(sfactor, dfactor);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::bindShader(RenderCmdsCache::ShaderType type)
{
	auto fun = [this, type]() {
		if (type == ShaderTexture) {
			BindShader draw(mTextureShaderProgram, mRect);
			draw.invoke();
		}
		else if (type == ShaderColor) {
			BindShader draw(mColorShaderProgram, mRect);
			draw.invoke();
		}
	};
	mglFuncs.push_back(fun);
}

void RenderCmdsCache::drawColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	auto fun = [this, r, g, b, a]() {
		DrawColor draw(mColorShaderProgram, spine::Color(r, g, b, a));
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::lineWidth(GLfloat width)
{
	auto fun = [width]() {
		LineWidth draw(width);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::pointSize(GLfloat pointSize)
{
	auto fun = [pointSize]() {
		PointSize draw(pointSize);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::drawPoly(const Point *points, int pointCount)
{
	auto fun = [this, points, pointCount]() {
		DrawPolygon draw(mColorShaderProgram, points, pointCount);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::drawLine(const Point &origin, const Point &destination)
{
	auto fun = [this, origin, destination]() {
		DrawLine draw(mColorShaderProgram, origin, destination);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::drawPoint(const Point &point)
{
	auto fun = [this, point]() {
		DrawPoint draw(mColorShaderProgram, point);
		draw.invoke();
	};
    //mglFuncs.push_back(fun);
}

void RenderCmdsCache::render()
{
    if(!mTextureShaderProgram || !mColorShaderProgram)
        return;
    if (mglFuncs.empty()) {
        if (cacheRendered)cacheRendered();
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &func : mglFuncs)
        func();
    clearCache();
    if (cacheRendered)cacheRendered();
}

void RenderCmdsCache::setSkeletonRect(const RectF &rect)
{
    mRect = rect;
}

void RenderCmdsCache::initShaderProgram()
{
    if(m_shaderInited)
        return;
    mTextureShaderProgram = new MyOpenGLShaderProgram();
#ifdef USE_QT_PROGRAM
	QOpenGLShader::ShaderType vertexShader = QOpenGLShader::Vertex, fragmentShader = QOpenGLShader::Fragment;
#else
	int vertexShader = GL_VERTEX_SHADER, fragmentShader = GL_FRAGMENT_SHADER;
#endif
    bool res = mTextureShaderProgram->addShaderFromSourceFile(vertexShader, "./shader/texture.vert");
	assert(res);
    res = mTextureShaderProgram->addShaderFromSourceFile(fragmentShader, "./shader/texture.frag");
	assert(res);
    res = mTextureShaderProgram->link();
	assert(res);

    mColorShaderProgram = new MyOpenGLShaderProgram();
    res = mColorShaderProgram->addShaderFromSourceFile(vertexShader, "./shader/color.vert");
	assert(res);

    res = mColorShaderProgram->addShaderFromSourceFile(fragmentShader, "./shader/color.frag");
	assert(res);
    res = mColorShaderProgram->link();
	assert(res);
    m_shaderInited = true;
}

bool RenderCmdsCache::isValid()
{
    return m_shaderInited;
}
