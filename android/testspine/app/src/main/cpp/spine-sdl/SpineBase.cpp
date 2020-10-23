#define SPINE_SHORT_NAMES
#include "SpineBase.h"
#include <assert.h>

_SP_ARRAY_IMPLEMENT_TYPE(spColorArray, spColor)
#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

//spine-c需要定义这两个函数
void _AtlasPage_createTexture(AtlasPage* self, const char* path) {
	spine::SkeletonDrawableBase *base = (spine::SkeletonDrawableBase*)self->atlas->rendererObject;
	if (nullptr != base) {
		spine::TextureBase *texture = base->createTexture(path);
		if (nullptr != texture) {
			self->width = texture->width();
			self->height = texture->height();
		}
		self->rendererObject = texture;
	}
	else {
		assert(false);
	}
}

void _AtlasPage_disposeTexture(AtlasPage* self) {
	if (self->rendererObject != NULL) {
		spine::TextureBase *texture = (spine::TextureBase*)self->rendererObject;
		delete texture;
	}
}

namespace spine {

VertexArray::VertexArray() {
	m_primitiveType = Points;
}

void VertexArray::clear()
{
	m_vertices.clear();
}

Vertex::Vertex()
{

}

Vector2f::Vector2f() {};
Vector2i::Vector2i() {};
Vector2u::Vector2u() {};
Vector2f::Vector2f(float ax, float ay) :x(ax), y(ay) {};
Vector2i::Vector2i(int ax, int ay) :x(ax), y(ay) {};
Vector2u::Vector2u(unsigned int ax, unsigned int ay) :x(ax), y(ay) {};

VertexArray::VertexArray(PrimitiveType type, std::size_t vertexCount)
	:m_primitiveType(type), m_vertices(vertexCount)
{

}

void VertexArray::append(const Vertex& vertex)
{
	m_vertices.push_back(vertex);
}

void VertexArray::setPrimitiveType(PrimitiveType type) {
	m_primitiveType = type;
}

PrimitiveType VertexArray::getPrimitiveType() const {
	return m_primitiveType;
}

const std::vector<Vertex>* VertexArray::getVertices()const {
	return &m_vertices;
}

TextureBase::TextureBase() {

}

TextureBase::~TextureBase() {

}

RenderBase::RenderBase() 
	: mViewWidth()
	, mViewHeight()
{

}

RenderBase::~RenderBase() {

}

SkeletonDrawableBase::SkeletonDrawableBase()
	: mScale(1.f)
	, mYDown(true)
	, usePremultipliedAlpha(false)
	, atlas(nullptr)
	, skeletonData(nullptr)
	, skeleton()
	, timeScale(1.f)
	, vertexArray(nullptr)
	, vertexEffect(nullptr)
	, worldVertices(nullptr)
	, clipper(nullptr)
	, tempUvs(nullptr)
	, tempColors(nullptr)
	, stateData(nullptr)
	, state(nullptr)
{

}

SkeletonDrawableBase::~SkeletonDrawableBase() {
	dispose();
}

void SkeletonDrawableBase::setScale(float scale) {
	mScale = scale;
}

void SkeletonDrawableBase::setBoneYDown(bool yDown) {
	mYDown = yDown;
}

void SkeletonDrawableBase::setUsePremultipliedAlpha(bool isUsePremultipliedAlpha) {
	usePremultipliedAlpha = isUsePremultipliedAlpha;
}

bool SkeletonDrawableBase::create(const char *atlasFile, const char*skeletonJsonFile) {
	bool ret = false;
	SkeletonJson* json = nullptr;

	do
	{
		if (nullptr == atlasFile || nullptr == skeletonJsonFile) {
			assert(false);
			break;
		}
		if (nullptr == (atlas = Atlas_createFromFile(atlasFile, this))) {
			assert(false);
			break;
		}
		if (nullptr == (json = SkeletonJson_create(atlas))) {
			assert(false);
			break;
		}
		json->scale = mScale;
		if (nullptr == (skeletonData = SkeletonJson_readSkeletonDataFile(json, skeletonJsonFile))) {
			assert(false);
			break;
		}
		if (!innerInit()) {
			assert(false);
			break;
		}
		ret = true;
	} while (false);

	if (nullptr != json) {
		SkeletonJson_dispose(json);
	}

	if (!ret) {
		dispose();
	}
	return ret;
}

void SkeletonDrawableBase::dispose() {
	if (nullptr != atlas) {
		Atlas_dispose(atlas);
		atlas = nullptr;
	}
	if (nullptr != skeletonData) {
		SkeletonData_dispose(skeletonData);
		skeletonData = nullptr;
	}
	if (nullptr != skeleton) {
		Skeleton_dispose(skeleton);
		skeleton = nullptr;
	}
	if (nullptr != vertexArray) {
		delete vertexArray;
		vertexArray = nullptr;
	}
	if (nullptr != vertexEffect) {
		assert(false);//todo
		vertexEffect = nullptr;
	}
	if (nullptr != worldVertices) {
		FREE(worldVertices);
		worldVertices = nullptr;
	}
	if (nullptr != clipper) {
		spSkeletonClipping_dispose(clipper);
		clipper = nullptr;
	}
	if (nullptr != tempUvs) {
		spFloatArray_dispose(tempUvs);
		tempUvs = nullptr;
	}
	if (nullptr != tempColors) {
		spColorArray_dispose(tempColors);
		tempColors = nullptr;
	}
	if (nullptr != stateData) {
		AnimationStateData_dispose(stateData);
		stateData = nullptr;
	}
	if (nullptr != state) {
		AnimationState_dispose(state);
		state = nullptr;
	}
}

spTrackEntry* SkeletonDrawableBase::tryAnimation(const char* animation, bool resetdrawstatus, bool repeat)
{
	spTrackEntry* entry = NULL;
	if (SkeletonData_findAnimation(skeletonData, animation))
	{
		if (resetdrawstatus)
		{
			Skeleton_setBonesToSetupPose(skeleton);
			Skeleton_setSlotsToSetupPose(skeleton);
			AnimationState_clearTracks(state);
		}

		spTrackEntry* entry = AnimationState_setAnimationByName(state, 0, animation, repeat);
		if (entry)
		{
			entry->listener = SkeletonDrawableBase::listenAnimations;
			entry->userData = this;
		}
	}
	return entry;
}

void SkeletonDrawableBase::update(float deltaTime) {
	Skeleton_update(skeleton, deltaTime);
	AnimationState_update(state, deltaTime * timeScale);
	AnimationState_apply(state, skeleton);
	Skeleton_updateWorldTransform(skeleton);
}

bool SkeletonDrawableBase::innerInit() {
	vertexEffect = 0;
	vertexArray = new VertexArray(Triangles, skeletonData->bonesCount * 4);
	Bone_setYDown(mYDown);
	worldVertices = MALLOC(float, SPINE_MESH_VERTEX_COUNT_MAX);
	skeleton = Skeleton_create(skeletonData);
	tempUvs = spFloatArray_create(16);
	tempColors = spColorArray_create(16);

	stateData = AnimationStateData_create(skeletonData);
	state = AnimationState_create(stateData);

	state->listener = SkeletonDrawableBase::listenAnimations;
	state->userData = this;

	clipper = spSkeletonClipping_create();

	return true;
}


void SkeletonDrawableBase::listenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
	SkeletonDrawableBase *pThis = reinterpret_cast<SkeletonDrawableBase*>(state->userData);
	if (nullptr != pThis) {
		pThis->onListenAnimations(state, type, entry, event);
	}
	else {
		assert(false);
	}
}

void SkeletonDrawableBase::draw(RenderBase* states)
{
	vertexArray->clear();
	TextureBase *statesTexture = nullptr;
	BlendMode statesBlendMode = BLENDMODE_NONE;
	unsigned short quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

	if (vertexEffect != 0)
		vertexEffect->begin(vertexEffect, skeleton);

	Vertex vertex;
	TextureBase* texture = 0;

	for (int i = 0; i < skeleton->slotsCount; ++i) {
		Slot* slot = skeleton->drawOrder[i];
		Attachment* attachment = slot->attachment;
		if (!attachment) continue;

		float* vertices = worldVertices;
		int verticesCount = 0;
		float* uvs = 0;
		unsigned short* indices = 0;
		int indicesCount = 0;
		spColor* attachmentColor;

		if (attachment->type == ATTACHMENT_REGION) {
			RegionAttachment* regionAttachment = (RegionAttachment*)attachment;
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, vertices, 0, 2);
			verticesCount = 4;
			uvs = regionAttachment->uvs;
			indices = quadIndices;
			indicesCount = 6;
			texture = (TextureBase*)((AtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
			attachmentColor = &regionAttachment->color;

		}
		else if (attachment->type == ATTACHMENT_MESH) {
			MeshAttachment* mesh = (MeshAttachment*)attachment;
			if (mesh->super.worldVerticesLength > SPINE_MESH_VERTEX_COUNT_MAX) continue;
			AtlasRegion *atlasRegion = (AtlasRegion*)mesh->rendererObject;
			texture = (TextureBase*)((AtlasRegion*)mesh->rendererObject)->page->rendererObject;
			spVertexAttachment_computeWorldVertices(SUPER(mesh), slot, 0, mesh->super.worldVerticesLength, worldVertices, 0, 2);
			verticesCount = mesh->super.worldVerticesLength >> 1;
			uvs = mesh->uvs;
			indices = mesh->triangles;
			indicesCount = mesh->trianglesCount;
			attachmentColor = &mesh->color;
		}
		else if (attachment->type == SP_ATTACHMENT_CLIPPING) {
			spClippingAttachment* clip = (spClippingAttachment*)slot->attachment;
			spSkeletonClipping_clipStart(clipper, slot, clip);
			continue;
		}
		else continue;

		uint8_t r = static_cast<uint8_t>(skeleton->color.r * slot->color.r * attachmentColor->r * 255);
		uint8_t g = static_cast<uint8_t>(skeleton->color.g * slot->color.g * attachmentColor->g * 255);
		uint8_t b = static_cast<uint8_t>(skeleton->color.b * slot->color.b * attachmentColor->b * 255);
		uint8_t a = static_cast<uint8_t>(skeleton->color.a * slot->color.a * attachmentColor->a * 255);
		vertex.color.r = r;
		vertex.color.g = g;
		vertex.color.b = b;
		vertex.color.a = a;

		spColor light;
		light.r = r / 255.0f;
		light.g = g / 255.0f;
		light.b = b / 255.0f;
		light.a = a / 255.0f;

		unsigned int blend = 0;
		switch (slot->data->blendMode) {
		case BLEND_MODE_NORMAL:
			blend = BLENDMODE_NORMAL;
			break;
		case BLEND_MODE_ADDITIVE:
			blend = BLENDMODE_ADDITIVE;
			break;
		case BLEND_MODE_MULTIPLY:
			blend = BLENDMODE_MULTIPLY;
			break;
		case BLEND_MODE_SCREEN:
			blend = BLENDMODE_SCREEN;
			break;
		default:
			blend = BLENDMODE_NORMAL;
			break;
		}
		if (usePremultipliedAlpha) {
			blend |= BLENDMODE_PMA;

		}

		if (statesTexture == 0) statesTexture = texture;

		if (statesBlendMode != blend || statesTexture != texture) {
			//SDL——Rendering
			callDraw(states, statesTexture, statesBlendMode, vertexArray);
			vertexArray->clear();
			statesBlendMode = (BlendMode)blend;
			statesTexture = texture;
		}

		if (spSkeletonClipping_isClipping(clipper)) {
			spSkeletonClipping_clipTriangles(clipper, vertices, verticesCount << 1, indices, indicesCount, uvs, 2);
			vertices = clipper->clippedVertices->items;
			verticesCount = clipper->clippedVertices->size >> 1;
			uvs = clipper->clippedUVs->items;
			indices = clipper->clippedTriangles->items;
			indicesCount = clipper->clippedTriangles->size;
		}

		if (vertexEffect != 0) {
			spFloatArray_clear(tempUvs);
			spColorArray_clear(tempColors);
			for (int i = 0; i < verticesCount; i++) {
				spColor vertexColor = light;
				spColor dark;
				dark.r = dark.g = dark.b = dark.a = 0;
				int index = i << 1;
				float x = vertices[index];
				float y = vertices[index + 1];
				float u = uvs[index];
				float v = uvs[index + 1];
				vertexEffect->transform(vertexEffect, &x, &y, &u, &v, &vertexColor, &dark);
				vertices[index] = x;
				vertices[index + 1] = y;
				spFloatArray_add(tempUvs, u);
				spFloatArray_add(tempUvs, v);
				spColorArray_add(tempColors, vertexColor);
			}

			for (int i = 0; i < indicesCount; ++i) {
				int index = indices[i] << 1;
				vertex.position.x = vertices[index];
				vertex.position.y = vertices[index + 1];
				vertex.texCoords.x = uvs[index];
				vertex.texCoords.y = uvs[index + 1];
				spColor vertexColor = tempColors->items[index >> 1];
				vertex.color.r = static_cast<uint8_t>(vertexColor.r * 255);
				vertex.color.g = static_cast<uint8_t>(vertexColor.g * 255);
				vertex.color.b = static_cast<uint8_t>(vertexColor.b * 255);
				vertex.color.a = static_cast<uint8_t>(vertexColor.a * 255);
				vertexArray->append(vertex);
			}
		}
		else {
			for (int i = 0; i < indicesCount; ++i) {
				int index = indices[i] << 1;
				vertex.position.x = vertices[index];
				vertex.position.y = vertices[index + 1];
				vertex.texCoords.x = uvs[index];
				vertex.texCoords.y = uvs[index + 1];
				vertexArray->append(vertex);
			}
		}

		spSkeletonClipping_clipEnd(clipper, slot);
	}

	//SDL——Rendering
	callDraw(states, statesTexture, statesBlendMode, vertexArray);

	spSkeletonClipping_clipEnd2(clipper);

	if (vertexEffect != 0)
		vertexEffect->end(vertexEffect);
}

void SkeletonDrawableBase::callDraw(RenderBase* states, TextureBase *texture, BlendMode blendMode, VertexArray* vertexArray) {
	if (nullptr != states && nullptr != texture && nullptr != vertexArray) {
		states->draw(texture, blendMode, vertexArray->getPrimitiveType(), vertexArray->getVertices());
	}
}
}