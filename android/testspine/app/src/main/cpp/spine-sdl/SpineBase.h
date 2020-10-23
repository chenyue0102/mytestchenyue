#ifndef Spine_Base_h_
#define Spine_Base_h_

#include <vector>
#include <stdint.h>
#include "spine/spine.h"
#include "spine/extension.h"

_SP_ARRAY_DECLARE_TYPE(spColorArray, spColor)
namespace spine {


typedef enum
{
	BLENDMODE_NONE = 0x00000000,
	BLENDMODE_NORMAL = 0x00000001,
	BLENDMODE_ADDITIVE = 0x00000002,
	BLENDMODE_MULTIPLY = 0x00000004,
	BLENDMODE_SCREEN = 0x00000008,
	BLENDMODE_MASK = 0x0000000F,
	BLENDMODE_PMA = 0x80000000,
} BlendMode;

enum PrimitiveType
{
	Points,        ///< List of individual points
	Lines,         ///< List of individual lines
	LineStrip,     ///< List of connected lines, a point uses the previous point to form a line
	Triangles,     ///< List of individual triangles
	TriangleStrip, ///< List of connected triangles, a point uses the two previous points to form a triangle
	TriangleFan,   ///< List of connected triangles, a point uses the common center and the previous point to form a triangle
};

class Vector2i
{
public:
	Vector2i();
	Vector2i(int X, int Y);
	int x; ///< X coordinate of the vector
	int y; ///< Y coordinate of the vector
};

class Vector2u
{
public:
	Vector2u();
	Vector2u(unsigned int X, unsigned int Y);
	unsigned int x; ///< X coordinate of the vector
	unsigned int y; ///< Y coordinate of the vector
};

class Vector2f
{
public:
	Vector2f();
	Vector2f(float X, float Y);
	float x; ///< X coordinate of the vector
	float y; ///< Y coordinate of the vector
};

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

class Vertex
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	////////////////////////////////////////////////////////////
	Vertex();


	Vertex(const Vector2f& thePosition);
	Vertex(const Vector2f& thePosition, const Color& theColor);
	Vertex(const Vector2f& thePosition, const Vector2f& theTexCoords);
	Vertex(const Vector2f& thePosition, const Color& theColor, const Vector2f& theTexCoords);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Vector2f  position;
	Color    color;
	Vector2f  texCoords;
};

class TextureBase {
public:
	TextureBase();
	virtual ~TextureBase();
public:
	virtual int width()const = 0;
	virtual int height()const = 0;
};

class RenderBase {
public:
	RenderBase();
	virtual ~RenderBase();
public:
	virtual void draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray) = 0;
};

class VertexArray
{
public:

	VertexArray();

	explicit VertexArray(PrimitiveType type, std::size_t vertexCount = 0);

	void clear();

	void append(const Vertex& vertex);

	void setPrimitiveType(PrimitiveType type);

	PrimitiveType getPrimitiveType() const;
	const std::vector<Vertex>* getVertices()const;

private:

	// Member data
	std::vector<Vertex> m_vertices;      ///< Vertices contained in the array
	PrimitiveType       m_primitiveType; ///< Type of primitives to draw
};

class SkeletonDrawableBase {
public:
	SkeletonDrawableBase();
	virtual ~SkeletonDrawableBase();
public:
	void setScale(float scale);
	void setBoneYDown(bool yDown);
	void setUsePremultipliedAlpha(bool isUsePremultipliedAlpha);
	bool create(const char *atlasFile, const char*skeletonJsonFile);
	void dispose();
public:
	spTrackEntry* tryAnimation(const char* animation, bool reset, bool repeat);
	void update(float deltaTime);

public:
	virtual TextureBase* createTexture(const char *path) = 0;
	void draw(RenderBase* states);

protected:
	virtual void onListenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) = 0;

private:
	bool innerInit();
	void callDraw(RenderBase* states, TextureBase *texture, BlendMode blendMode, VertexArray* vertexArray);

public:
	static void listenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event);

public:
	float mScale;
	bool mYDown;
	bool usePremultipliedAlpha;//pre multiply alpha or not

	spAtlas* atlas;
	spSkeletonData* skeletonData;
	spSkeleton* skeleton;
	float timeScale;
	VertexArray* vertexArray;
	spVertexEffect* vertexEffect;
	float* worldVertices;
	spSkeletonClipping* clipper;
	spFloatArray* tempUvs;
	spColorArray* tempColors;
	spAnimationStateData* stateData;
	spAnimationState* state;
};
}

#endif