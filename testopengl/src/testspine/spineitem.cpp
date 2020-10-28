#include "spineitem.h"

#include <spine/spine.h>
#include <float.h>
#include <stdlib.h>
#include "rendercmdscache.h"
#include "texture.h"

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

bool contains(std::vector<std::string> &array, const std::string &text) {
	for (auto &s : array) {
		if (s == text) {
			return true;
		}
	}
	return false;
}

spine::String convert(const MyString &str) {
	return spine::String(str.c_str());
}

MyColor convert(const spine::Color &clr) {
	return MyColor(clr.r, clr.g, clr.b, clr.a);
}

void animationSateListioner(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event) {
    auto spItem = static_cast<SpineItem*>(state->getRendererObject());
    if(!spItem)
        return;
    MyString animationName = MyString(entry->getAnimation()->getName().buffer());
    switch (type) {
    case spine::EventType_Start:{
        spItem->animationStarted(entry->getTrackIndex(), animationName);
        if(spItem->isVisible() && !spItem->m_animating) {
            spItem->m_animating = true;
            spItem->animationUpdated();
        }
        break;
    }
    case spine::EventType_Interrupt: {
        spItem->animationInterrupted(entry->getTrackIndex(), animationName);
        break;
    }
    case spine::EventType_End: {
        spItem->animationEnded(entry->getTrackIndex(), animationName);
        break;
    }
    case spine::EventType_Complete: {
        spItem->animationCompleted(entry->getTrackIndex(), animationName);
        break;
    }
    case spine::EventType_Dispose: {
        spItem->animationDisposed(entry->getTrackIndex(), animationName);
        break;
    }
    case spine::EventType_Event: {
        break;
    }
    }
}

SpineItem::SpineItem() :
    m_clipper(new spine::SkeletonClipping)
{
    m_blendColor = MyColor(255, 255, 255, 255);
}

SpineItem::~SpineItem()
{
    if(m_animationState)
        m_animationState->clearTracks();
    m_requestDestroy = true;
    releaseSkeletonRelatedData();
}

void SpineItem::setAtlasFile(const std::string &atlasPath)
{
	m_atlasFile = atlasPath;
}

void SpineItem::setSkeletonFile(const std::string &skeletonPath)
{
	m_skeletonFile = skeletonPath;
	skeletonFileChanged(skeletonPath);
}

bool SpineItem::create() {
	releaseSkeletonRelatedData();
	m_isLoading = true;

	m_loaded = false;
	m_animations.clear();
	m_skins.clear();
	m_scaleX = 1.0;
	m_scaleY = 1.0;
	scaleXChanged(m_scaleX);
	scaleYChanged(m_scaleY);
	loadedChanged(m_loaded);
	isSkeletonReadyChanged(isSkeletonReady());

	if (m_atlasFile.empty()) {
		resourceLoadFailed();
		assert(false);
		return false;
	}

	if (m_skeletonFile.empty()) {
		resourceLoadFailed();
		assert(false);
		return false;
	}

	m_atlas.reset(new spine::Atlas(m_atlasFile.c_str(),
		AimyTextureLoader::instance()));

	if (m_atlas->getPages().size() == 0) {
		resourceLoadFailed();
		assert(false);
		return false;
	}

	spine::SkeletonJson json(m_atlas.get());
	json.setScale(1);
	m_skeletonData.reset(json.readSkeletonDataFile(m_skeletonFile.c_str()));
	if (!m_skeletonData) {
		resourceLoadFailed();
		assert(false);
		return false;
	}

	m_skeleton.reset(new spine::Skeleton(m_skeletonData.get()));
	m_skeleton->setX(0);
	m_skeleton->setY(0);
	m_animationStateData.reset(new spine::AnimationStateData(m_skeletonData.get()));
	m_animationStateData->setDefaultMix(m_defaultMix);

	m_animationState.reset(new spine::AnimationState(m_animationStateData.get()));
	m_animationState->setRendererObject(this);
	m_animationState->setListener(animationSateListioner);
	m_loaded = true;
	m_isLoading = false;

	auto animations = m_skeletonData->getAnimations();
	for (size_t i = 0; i < animations.size(); i++) {
		auto aniName = std::string(animations[i]->getName().buffer());
		m_animations.push_back(aniName);
	}
	animationsChanged(m_animations);

	auto skins = m_skeletonData->getSkins();
	for (size_t i = 0; i < skins.size(); i++) {
		auto skinName = std::string(skins[i]->getName().buffer());
		m_skins.push_back(skinName);
	}

	m_skeleton->setScaleX(m_skeletonScale * m_scaleX);
	m_skeleton->setScaleY(m_skeletonScale * m_scaleY);

	skinsChanged(m_skins);
	loadedChanged(m_loaded);
	isSkeletonReadyChanged(isSkeletonReady());

	m_skeleton->updateWorldTransform();
	m_boundingRect = computeBoundingRect();
	//batchRenderCmd();
	animationUpdated();
	resourceReady();
	return true;
}

void SpineItem::setToSetupPose()
{
	if (!isSkeletonReady()) {
		return;
	}
	m_skeleton->setToSetupPose();
	m_animationState->apply(*m_skeleton.get());
	m_skeleton->updateWorldTransform();
}

void SpineItem::setBonesToSetupPose()
{
	if (!isSkeletonReady()) {
		return;
	}
	m_skeleton->setBonesToSetupPose();
}

void SpineItem::setSlotsToSetupPose()
{
	if (!isSkeletonReady()) {
		return;
	}
	m_skeleton->setSlotsToSetupPose();
}

bool SpineItem::setAttachment(const MyString &slotName, const MyString &attachmentName)
{
	if (!isSkeletonReady()) {
		return false;
	}
	m_skeleton->setAttachment(convert(slotName), convert(attachmentName));
	return true;
}

void SpineItem::setMix(const MyString &fromAnimation, const MyString &toAnimation, float duration)
{
	if (!isSkeletonReady()) {
		return;
	}
	m_animationStateData->setMix(convert(fromAnimation),
		convert(toAnimation),
		duration);
}

void SpineItem::setAnimation(int trackIndex, const MyString &name, bool loop)
{
	if (!isSkeletonReady()) {
		return;
	}
	if (!contains(m_animations, name)) {
		return;
	}
	m_animationState->setAnimation(size_t(trackIndex), convert(name), loop);
}

void SpineItem::addAnimation(int trackIndex, const MyString &name, bool loop, float delay)
{
	if (!isSkeletonReady()) {
		return;
	}
	if (!contains(m_animations, name)) {
		return;
	}
	m_animationState->addAnimation(size_t(trackIndex), convert(name), loop, delay);
}

void SpineItem::setSkin(const MyString &skinName)
{
	if (!isSkeletonReady()) {
		return;
	}
	if (!contains(m_skins, skinName)) {
	}
	m_skeleton->setSkin(convert(skinName));
}

void SpineItem::clearTracks()
{
	if (!isSkeletonReady()) {
		return;
	}
	m_animationState->clearTracks();
	m_animating = false;
}

void SpineItem::clearTrack(int trackIndex)
{
	if (!isSkeletonReady()) {
		return;
	}
	m_animationState->clearTrack(size_t(trackIndex));
	if (m_animationState->getTracks().size() <= 0)
		m_animating = false;
}

void SpineItem::updateSkeletonAnimation(float deltaTime)
{
	if (!isSkeletonReady()) {
		return;
	}

	m_skeleton->update(deltaTime);
	m_animationState->update(deltaTime);
	m_animationState->apply(*m_skeleton.get());
	m_skeleton->updateWorldTransform();

	m_boundingRect = computeBoundingRect();
	//m_spItem->batchRenderCmd();
	animationUpdated();
}

void makeVectorSize(spine::Vector<float> &vt, size_t minSize) {
	if (vt.size() < minSize) {
		vt.setSize(minSize, 0.0f);
	}
}

MyRect SpineItem::computeBoundingRect()
{
    if(!isSkeletonReady())
        return MyRect();
    float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;
    float vminX = FLT_MAX, vminY = FLT_MAX, vmaxX = -FLT_MAX, vmaxY = -FLT_MAX;
    for(size_t i = 0; i < m_skeleton->getSlots().size(); i++) {
        auto slot = m_skeleton->getSlots()[i];
        if(!slot->getAttachment())
            continue;
        int verticesCount;
        auto* attachment = slot->getAttachment();
        if(attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
            auto* regionAttachment = static_cast<spine::RegionAttachment*>(slot->getAttachment());
			makeVectorSize(m_MyWorldVertices, 0 + 8);
            regionAttachment->computeWorldVertices(slot->getBone(), m_MyWorldVertices, 0, 2);
            verticesCount = 8;
            // handle viewport mode
			std::string tmp = std::string(attachment->getName().buffer());
            if(tmp.rfind("viewport") == (tmp.size() - strlen("viewport"))) {
                m_hasViewPort = true;
                for (int ii = 0; ii < verticesCount; ii+=2) {
                    float x = m_MyWorldVertices[ii], y = m_MyWorldVertices[ii + 1];
                    vminX = min(vminX, x);
                    vminY = min(vminY, y);
                    vmaxX = max(vmaxX, x);
                    vmaxY = max(vmaxY, y);
                }
                m_viewPortRect = MyRect(vminX, vminY, vmaxX - vminX, vmaxY - vminY);
            }
        } else if(attachment->getRTTI().isExactly(spine::MeshAttachment::rtti)) {
            auto* meshAttachment = static_cast<spine::MeshAttachment*>(slot->getAttachment());
            verticesCount = meshAttachment->getWorldVerticesLength();
			makeVectorSize(m_MyWorldVertices, verticesCount);
            meshAttachment->computeWorldVertices(*slot, m_MyWorldVertices);
			std::string tmp = std::string(attachment->getName().buffer());
            if(tmp.rfind("viewport") == (tmp.size() - strlen("viewport"))) {
                m_hasViewPort = true;
                for (int ii = 0; ii < verticesCount; ii+=2) {
                    float x = m_MyWorldVertices[ii], y = m_MyWorldVertices[ii + 1];
                    vminX = min(vminX, x);
                    vminY = min(vminY, y);
                    vmaxX = max(vmaxX, x);
                    vmaxY = max(vmaxY, y);
                }
                m_viewPortRect = MyRect(vminX, vminY, vmaxX - vminX, vmaxY - vminY);
            }
        } else
            continue;
        for (int ii = 0; ii < verticesCount; ii+=2) {
            float x = m_MyWorldVertices[ii], y = m_MyWorldVertices[ii + 1];
            minX = min(minX, x);
            minY = min(minY, y);
            maxX = max(maxX, x);
            maxY = max(maxY, y);
        }
    }
    return MyRect(minX, minY, maxX - minX, maxY - minY);
}

Texture *SpineItem::getTexture(spine::Attachment *attachment) const
{
    if(attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
        return (Texture*)((spine::AtlasRegion*)static_cast<spine::RegionAttachment*>(attachment)->getRendererObject())->page->getRendererObject();
    } else if(attachment->getRTTI().isExactly(spine::MeshAttachment::rtti)) {
        return (Texture*)((spine::AtlasRegion*)static_cast<spine::MeshAttachment*>(attachment)->getRendererObject())->page->getRendererObject();
    }
    return nullptr;
}

void SpineItem::releaseSkeletonRelatedData(){
    m_hasViewPort = false;
    m_animationStateData.reset();
    m_animationState.reset();
    m_skeletonData.reset();
    m_atlas.reset();
    m_skeleton.reset();
    m_loaded = false;
    m_shouldReleaseCacheTexture = true;
}

bool SpineItem::nothingToDraw(spine::Slot &slot)
{
    auto attachMent = slot.getAttachment();
    if(!attachMent ||
        !slot.getBone().isActive() ||
        slot.getColor().a == 0)
        return true;
    if(attachMent->getRTTI().isExactly(spine::RegionAttachment::rtti)){
        if(static_cast<spine::RegionAttachment*>(attachMent)->getColor().a == 0)
            return true;
    }
    else if (attachMent->getRTTI().isExactly(spine::MeshAttachment::rtti)){
            if(static_cast<spine::MeshAttachment*>(attachMent)->getColor().a == 0)
                return true;
    }
    return false;
}

static unsigned short quadIndices[] = {0, 1, 2, 2, 3, 0};

void SpineItem::batchRenderCmd(RenderCmdsCache *render)
{
	auto m_renderCache = render;
	if (m_requestRender) {
		assert(false);
		return;
	}
    m_requestRender = true;
	if (!m_renderCache || !m_renderCache->isValid()) {
		assert(false);
		return;
	}
        

    m_batches.clear();

    for(size_t i = 0, n = m_skeleton->getSlots().size(); i < n; ++i) {
        auto slot = m_skeleton->getDrawOrder()[i];

        if (nothingToDraw(*slot)) {
            m_clipper->clipEnd(*slot);
            continue;
        }

        auto* attachment = slot->getAttachment();
        if (!attachment)
            continue;

        RenderCmdBatch batch;

        auto name = std::string(attachment->getName().buffer());
//        spine::Vector<SpineVertex> vertices;
//        spine::Vector<GLushort> triangles;
        Texture* texture = nullptr;
        int blendMode;
        blendMode = slot->getData().getBlendMode();


        auto skeletonColor = m_skeleton->getColor();
        auto slotColor = slot->getColor();
        MyColor attachmentColor(0, 0, 0, 0);
		MyColor tint(skeletonColor.r * slotColor.r,
                          skeletonColor.g * slotColor.g,
                          skeletonColor.b * slotColor.b,
                          skeletonColor.a * slotColor.a);

        // TODO: for premultiply alpha handling
//        spine::Color darkColor;

//        if(slot->hasDarkColor())
//            darkColor = slot->getDarkColor();
//        else{
//            darkColor.r = 0;
//            darkColor.g = 0;
//            darkColor.b = 0;
//        }
//        darkColor.a = 0;
        if(attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
            auto regionAttachment = (spine::RegionAttachment*)attachment;
            attachmentColor.set(convert(regionAttachment->getColor()));

            tint.set(tint.r * attachmentColor.r, tint.g * attachmentColor.g, tint.b * attachmentColor.b, tint.a * attachmentColor.a);
            texture = getTexture(regionAttachment);
            batch.vertices.resize(4, SpineVertex());
            regionAttachment->computeWorldVertices(slot->getBone(),
                                                   (float*)batch.vertices.data(),
                                                   0,
                                                   sizeof (SpineVertex) / sizeof (float));
            for(size_t j = 0, l = 0; j < 4; j++,l+=2) {
                auto &vertex = batch.vertices[j];
                vertex.color.set(tint);
                vertex.u = regionAttachment->getUVs()[l];
                vertex.v = regionAttachment->getUVs()[l + 1];
            }
            batch.triangles.resize(6);
            memcpy(batch.triangles.data(), quadIndices, 6 * sizeof (GLushort));
        } else if (attachment->getRTTI().isExactly(spine::MeshAttachment::rtti)) {
            auto mesh = (spine::MeshAttachment*)attachment;
            attachmentColor.set(convert(mesh->getColor()));
            tint.set(tint.r * attachmentColor.r, tint.g * attachmentColor.g, tint.b * attachmentColor.b, tint.a * attachmentColor.a);
            size_t numVertices = mesh->getWorldVerticesLength() / 2;
            batch.vertices.resize(numVertices, SpineVertex());
            texture = getTexture(mesh);
            mesh->computeWorldVertices(*slot,
                                       0,
                                       mesh->getWorldVerticesLength(),
                                       (float*)batch.vertices.data(),
                                       0,
                                       sizeof (SpineVertex) / sizeof (float));
            for (size_t j = 0, l = 0; j < numVertices; j++, l+=2) {
                auto& vertex = batch.vertices[j];
                vertex.color.set(tint);
                vertex.u = mesh->getUVs()[l];
                vertex.v = mesh->getUVs()[l+1];
            }
            batch.triangles.resize(mesh->getTriangles().size(), 0);
            memcpy(batch.triangles.data(), mesh->getTriangles().buffer(), mesh->getTriangles().size() * sizeof (GLushort));

            if (m_vertexEfect) {
                // todo
            }

        } else if(attachment->getRTTI().isExactly(spine::ClippingAttachment::rtti)) {
            auto clip = (spine::ClippingAttachment*)attachment;
            m_clipper->clipStart(*slot, clip);
            continue;
        } else{
            m_clipper->clipEnd(*slot);
            continue;
        }

        if(tint.a == 0) {
            m_clipper->clipEnd(*slot);
            continue;
        }

        if(texture) {
            if(m_clipper->isClipping()) {

                auto tmpVerticesCount = batch.vertices.size() * 2;
                spine::Vector<float> tmpVertices;
                spine::Vector<float> tmpUvs;
                tmpVertices.setSize(tmpVerticesCount, 0);
                tmpUvs.setSize(tmpVerticesCount, 0);

                for(size_t i = 0; i < batch.vertices.size(); i++) {
                    tmpVertices[i * 2] = batch.vertices[i].x;
                    tmpVertices[i * 2 + 1] = batch.vertices[i].y;
                    tmpUvs[i * 2] = batch.vertices[i].u;
                    tmpUvs[i * 2 + 1] = batch.vertices[i].v;
                }
                m_clipper->clipTriangles(tmpVertices.buffer(), batch.triangles.data(), batch.triangles.size(), tmpUvs.buffer(), sizeof (short));
                tmpVertices.setSize(0, 0);
                tmpUvs.setSize(0, 0);

                auto vertCount = m_clipper->getClippedVertices().size() / 2;

                if(m_clipper->getClippedTriangles().size() == 0) {
                    m_clipper->clipEnd(*slot);
                    continue;
                }
                batch.triangles.resize(m_clipper->getClippedTriangles().size(), 0);
                memcpy(batch.triangles.data(), m_clipper->getClippedTriangles().buffer(), batch.triangles.size() * sizeof (unsigned short));
                auto newUvs = m_clipper->getClippedUVs();
                auto newVertices = m_clipper->getClippedVertices();
                batch.vertices.resize(vertCount, SpineVertex());
                for(size_t i = 0; i < vertCount; i++) {
                    batch.vertices[i].x = newVertices[i * 2];
                    batch.vertices[i].y = newVertices[i * 2 + 1];
                    batch.vertices[i].u = newUvs[i * 2];
                    batch.vertices[i].v = newUvs[i * 2 + 1];
                    batch.vertices[i].color.set(tint);
                }
            }
            if(batch.triangles.size() == 0)
                m_clipper->clipEnd(*slot);

            batch.texture = texture;
            batch.blendMode = blendMode;
            m_batches.push_back(batch);
            m_clipper->clipEnd(*slot);
        }
    }
    m_clipper->clipEnd();
}

void SpineItem::renderToCache(RenderCmdsCache *render)
{
	RenderCmdsCache *m_renderCache = render;
    if(!m_renderCache || !m_renderCache->isValid())
        return;

	if (m_hasViewPort)
		m_renderCache->setSkeletonRect(m_viewPortRect);
	else
		m_renderCache->setSkeletonRect(m_boundingRect);

    m_renderCache->bindShader(RenderCmdsCache::ShaderTexture);
    bool hasBlend = false;
    for (const auto& batch: m_batches) {
        if(!batch.texture)
            continue;
        if(batch.triangles.size() == 0) {
            hasBlend = false;
            continue;
        }
        if(hasBlend) {
            switch (batch.blendMode) {
            case spine::BlendMode_Additive: {
                m_renderCache->blendFunc(GL_ONE, GL_ONE);
                break;
            }
            case spine::BlendMode_Multiply: {
                m_renderCache->blendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
                break;
            }
            case spine::BlendMode_Screen: {
                m_renderCache->blendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
                break;
            }
            default:{
                m_renderCache->blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                break;
            }
            }
        }

        m_renderCache->drawTriangles(
                    AimyTextureLoader::instance()->getGLTexture(batch.texture),
                    batch.vertices,
                    batch.triangles,
					m_blendColor,
                    m_blendColorChannel,
                    m_light);
        hasBlend = true;

#ifdef _DEBUG
        // debug drawing
        if(m_debugBones || m_debugSlots || m_debugMesh) {
            m_renderCache->bindShader(RenderCmdsCache::ShaderColor);
            m_renderCache->blendFunc(GL_ONE, GL_ZERO);

            if(m_debugSlots) {
                m_renderCache->drawColor(200, 40, 150, 255);
                m_renderCache->lineWidth(1);
                MyPoint points[4];
                for (size_t i = 0, n = m_skeleton->getSlots().size(); i < n; i++) {
                    auto slot = m_skeleton->getSlots()[i];
                    if(!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(spine::RegionAttachment::rtti))
                        continue;
                    auto* regionAttachment = (spine::RegionAttachment*)slot->getAttachment();
					makeVectorSize(m_MyWorldVertices, 0 + 8);
                    regionAttachment->computeWorldVertices(slot->getBone(), m_MyWorldVertices, 0, 2);
                    points[0] = MyPoint(m_MyWorldVertices[0], m_MyWorldVertices[1]);
                    points[1] = MyPoint(m_MyWorldVertices[2], m_MyWorldVertices[3]);
                    points[2] = MyPoint(m_MyWorldVertices[4], m_MyWorldVertices[5]);
                    points[3] = MyPoint(m_MyWorldVertices[6], m_MyWorldVertices[7]);
                    m_renderCache->drawPoly(points, 4);
                }
            }

            if(m_debugMesh) {
                std::vector<MyPoint> points;
                m_renderCache->drawColor(40, 150, 200, 255);
                for (size_t i = 0, n = m_skeleton->getSlots().size(); i < n; i++) {
                    auto slot = m_skeleton->getSlots()[i];
                    if(!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(spine::MeshAttachment::rtti))
                        continue;
                    auto* mesh = (spine::MeshAttachment*)slot->getAttachment();
                    size_t numVertices = mesh->getWorldVerticesLength() / 2;
                    points.resize(numVertices);
                    mesh->computeWorldVertices(*slot,
                                               0,
                                               mesh->getWorldVerticesLength(),
                                               (float*)points.data(),
                                               0,
                                               sizeof (MyPoint) / sizeof (float));
                    m_renderCache->drawPoly(points.data(), points.size());
                }
            }

            if(m_debugBones) {
                m_renderCache->drawColor(200, 150, 40, 255);
                m_renderCache->lineWidth(2);
                for(int i = 0, n = m_skeleton->getBones().size(); i < n; i++) {
                    m_skeleton->updateWorldTransform();
                    auto bone = m_skeleton->getBones()[i];
                    if(!bone->isActive()) continue;
                    float x = bone->getData().getLength() * bone->getA() + bone->getWorldX();
                    float y = bone->getData().getLength() * bone->getC() + bone->getWorldY();
                    MyPoint p0(bone->getWorldX(), bone->getWorldY());
					MyPoint p1(x, y);
                    m_renderCache->drawLine(p0, p1);
                }
    //            cache->drawColor(0, 0, 255, 255);
                m_renderCache->pointSize(4.0);
                for(int i = 0, n = m_skeleton->getBones().size(); i < n; i++) {
                    auto bone = m_skeleton->getBones()[i];
                    m_renderCache->drawPoint(MyPoint(bone->getWorldX(), bone->getWorldY()));
                    if(i == 0) m_renderCache->drawColor(0, 255, 0,255);
                }
            }
        }
#endif
    }
    m_requestRender = false;
}

float SpineItem::light() const
{
    return m_light;
}

void SpineItem::setLight(float light)
{
    m_light = light;
    lightChanged(m_light);
}

bool SpineItem::debugMesh() const
{
    return m_debugMesh;
}

void SpineItem::setDebugMesh(bool debugMesh)
{
    m_debugMesh = debugMesh;
    debugMeshChanged(m_debugMesh);
}

int SpineItem::blendColorChannel() const
{
    return m_blendColorChannel;
}

void SpineItem::setBlendColorChannel(int blendColorChannel)
{
    m_blendColorChannel = blendColorChannel;
    blendColorChannelChanged(m_blendColorChannel);
}

MyColor SpineItem::blendColor() const
{
    return m_blendColor;
}

void SpineItem::setBlendColor(const MyColor &color)
{
    m_blendColor = color;
    blendColorChanged(color);
}

//QObject *SpineItem::vertexEfect() const
//{
//    return (QObject*)m_vertexEfect;
//}
//
//void SpineItem::setVertexEfect(QObject *vertexEfect)
//{
//    m_vertexEfect = (SpineVertexEffect*)vertexEfect;
//    emit vertexEfectChanged();
//}

float SpineItem::scaleY() const
{
    return m_scaleY;
}

void SpineItem::setScaleY(const float &value)
{
    m_scaleY = value;
    if(isSkeletonReady())
        m_skeleton->setScaleY(m_scaleY * m_skeletonScale);
    scaleYChanged(m_scaleY);
}

float SpineItem::scaleX() const
{
    return m_scaleX;
}

void SpineItem::setScaleX(const float &value)
{
    m_scaleX = value;
    if(isSkeletonReady())
        m_skeleton->setScaleX(m_scaleX * m_skeletonScale);
    scaleXChanged(m_scaleX);
}

float SpineItem::defaultMix() const
{
    return m_defaultMix;
}

void SpineItem::setDefaultMix(const float &defaultMix)
{
    m_defaultMix = defaultMix;
    defaultMixChanged(m_defaultMix);
    if(isSkeletonReady()) {
        m_animationStateData->setDefaultMix(m_defaultMix);
    }
}

float SpineItem::skeletonScale() const
{
    return m_skeletonScale;
}

void SpineItem::setSkeletonScale(const float &skeletonScale)
{
    if(m_isLoading)
        return;
    m_skeletonScale = skeletonScale;
    if(isSkeletonReady()) {
        m_skeleton->setScaleX(m_scaleX * m_skeletonScale);
        m_skeleton->setScaleY(m_scaleY * m_skeletonScale);
    }
    skeletonScaleChanged(m_skeletonScale);
}

std::vector<std::string> SpineItem::animations() const
{
    return m_animations;
}

std::vector<std::string> SpineItem::skins() const
{
    return m_skins;
}

bool SpineItem::debugSlots() const
{
    return m_debugSlots;
}

void SpineItem::setDebugSlots(bool debugSlots)
{
    m_debugSlots = debugSlots;
    debugSlotsChanged(m_debugSlots);
}

bool SpineItem::debugBones() const
{
    return m_debugBones;
}

void SpineItem::setDebugBones(bool debugBones)
{
    m_debugBones = debugBones;
    debugBonesChanged(m_debugBones);
}

bool SpineItem::loaded() const
{
    return m_loaded;
}

MySize SpineItem::sourceSize() const
{
    return m_sourceSize;
}

void SpineItem::setSourceSize(const MySize &sourceSize)
{
    m_sourceSize = sourceSize;
    sourceSizeChanged(m_sourceSize);
}

void SpineItem::updateBoundingRect()
{
    setSourceSize(MySize(m_boundingRect.width(), m_boundingRect.height()));
}

bool SpineItem::isSkeletonReady() const
{
    return m_loaded && m_atlas && m_skeleton && m_animationState;
}