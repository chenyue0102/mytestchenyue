#include "spineitem.h"

#include <spine/spine.h>
#include <float.h>
#include <stdlib.h>
#include "rendercmdscache.h"
#include "texture.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define qMin min
#define qMax max

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
    m_skeletonScale(1.0),
    m_clipper(new spine::SkeletonClipping),
    m_spWorker(new SpineItemWorker(this))
{
    m_blendColor = MyColor(255, 255, 255, 255);
    m_worldVertices = new float[2000];
}

SpineItem::~SpineItem()
{
    if(m_animationState)
        m_animationState->clearTracks();
    m_requestDestroy = true;
    m_spWorker.reset();
    releaseSkeletonRelatedData();
    delete [] m_worldVertices;
}

void SpineItem::setAtlasFile(const std::string &atlasPath)
{
	m_atlasFile = atlasPath;
	atlasFileChanged(atlasPath);
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
		return false;
	}

	if (m_skeletonFile.empty()) {
		resourceLoadFailed();
		return false;
	}

	m_atlas.reset(new spine::Atlas(m_atlasFile.c_str(),
		AimyTextureLoader::instance()));

	if (m_atlas->getPages().size() == 0) {
		resourceLoadFailed();
		return false;
	}

	spine::SkeletonJson json(m_atlas.get());
	json.setScale(1);
	m_skeletonData.reset(json.readSkeletonDataFile(m_skeletonFile.c_str()));
	if (!m_skeletonData) {
		resourceLoadFailed();
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
	for (int i = 0; i < animations.size(); i++) {
		auto aniName = std::string(animations[i]->getName().buffer());
		m_animations.push_back(aniName);
	}
	animationsChanged(m_animations);

	auto skins = m_skeletonData->getSkins();
	for (int i = 0; i < skins.size(); i++) {
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
    if(m_spWorker)
        m_spWorker->setToSetupPose();
}

void SpineItem::setBonesToSetupPose()
{
    if(m_spWorker)
        m_spWorker->setBonesToSetupPose();
}

void SpineItem::setSlotsToSetupPose()
{
    if(m_spWorker)
        m_spWorker->setSlotsToSetupPose();
}

bool SpineItem::setAttachment(const MyString &slotName, const MyString &attachmentName)
{
    if(m_spWorker)
        m_spWorker->setAttachment(slotName, attachmentName);
    return true;
}

void SpineItem::setMix(const MyString &fromAnimation, const MyString &toAnimation, float duration)
{
    if(m_spWorker)
        m_spWorker->setMix(fromAnimation, toAnimation, duration);
}

void SpineItem::setAnimation(int trackIndex, const MyString &name, bool loop)
{
    if(m_spWorker)
        m_spWorker->setAnimation(trackIndex, name, loop);
}

void SpineItem::addAnimation(int trackIndex, const MyString &name, bool loop, float delay)
{
    if(m_spWorker)
        m_spWorker->addAnimation(trackIndex, name, loop, delay);
}

void SpineItem::setSkin(const MyString &skinName)
{
    if(m_spWorker)
        m_spWorker->setSkin(skinName);
}

void SpineItem::clearTracks()
{
    if(m_spWorker)
        m_spWorker->clearTracks();
}

void SpineItem::clearTrack(int trackIndex)
{
    if(m_spWorker)
        m_spWorker->clearTrack(trackIndex);
}

void SpineItem::updateSkeletonAnimation()
{
	if (!isSkeletonReady()) {
		return;
	}

	/*if(!m_spItem->m_tickCounter.isValid())
		m_spItem->m_tickCounter.restart();
	else{
		auto sleepCount = 1000.0 / m_spItem->m_fps - m_spItem->m_tickCounter.elapsed();
		if(sleepCount > 0)
			QThread::msleep(sleepCount);
	}
	m_spItem->m_tickCounter.restart();*/

	if (m_animationState->getTracks().size() <= 0 || !isVisible()) {
		if (m_fadecounter > 0)
			m_fadecounter--;
		else
			return;
	}
	else
		m_fadecounter = 1;

	qint64 msecs = m_timer.getCurrentTimeMs();
	m_timer.setBaseTimeMs(0);
	const float deltaTime = msecs / 1000.0 * m_timeScale;
	m_animationState->update(deltaTime);
	m_animationState->apply(*m_skeleton.get());
	m_skeleton->updateWorldTransform();

	m_boundingRect = computeBoundingRect();
	//m_spItem->batchRenderCmd();
	emit animationUpdated();
}

RectF SpineItem::computeBoundingRect()
{
    if(!isSkeletonReady())
        return RectF();
    float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;
    float vminX = FLT_MAX, vminY = FLT_MAX, vmaxX = -FLT_MAX, vmaxY = -FLT_MAX;
    for(int i = 0; i < m_skeleton->getSlots().size(); i++) {
        auto slot = m_skeleton->getSlots()[i];
        if(!slot->getAttachment())
            continue;
        int verticesCount;
        auto* attachment = slot->getAttachment();
        if(attachment->getRTTI().isExactly(spine::RegionAttachment::rtti)) {
            auto* regionAttachment = static_cast<spine::RegionAttachment*>(slot->getAttachment());
            regionAttachment->computeWorldVertices(slot->getBone(), m_worldVertices, 0, 2);
            verticesCount = 8;
            // handle viewport mode
			std::string tmp = std::string(attachment->getName().buffer());
            if(tmp.rfind("viewport") == (tmp.size() - strlen("viewport"))) {
                m_hasViewPort = true;
                for (int ii = 0; ii < verticesCount; ii+=2) {
                    float x = m_worldVertices[ii], y = m_worldVertices[ii + 1];
                    vminX = qMin(vminX, x);
                    vminY = qMin(vminY, y);
                    vmaxX = qMax(vmaxX, x);
                    vmaxY = qMax(vmaxY, y);
                }
                m_viewPortRect = RectF(vminX, vminY, vmaxX - vminX, vmaxY - vminY);
            }
        } else if(attachment->getRTTI().isExactly(spine::MeshAttachment::rtti)) {
            auto* meshAttachment = static_cast<spine::MeshAttachment*>(slot->getAttachment());
            verticesCount = meshAttachment->getWorldVerticesLength();
            meshAttachment->computeWorldVertices(*slot, m_worldVertices);
			std::string tmp = std::string(attachment->getName().buffer());
            if(tmp.rfind("viewport") == (tmp.size() - strlen("viewport"))) {
                m_hasViewPort = true;
                for (int ii = 0; ii < verticesCount; ii+=2) {
                    float x = m_worldVertices[ii], y = m_worldVertices[ii + 1];
                    vminX = qMin(vminX, x);
                    vminY = qMin(vminY, y);
                    vmaxX = qMax(vmaxX, x);
                    vmaxY = qMax(vmaxY, y);
                }
                m_viewPortRect = RectF(vminX, vminY, vmaxX - vminX, vmaxY - vminY);
            }
        } else
            continue;
        for (int ii = 0; ii < verticesCount; ii+=2) {
            float x = m_worldVertices[ii], y = m_worldVertices[ii + 1];
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }
    return RectF(minX, minY, maxX - minX, maxY - minY);
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
    if(m_requestRender)
        return;
    m_requestRender = true;
    if(!m_renderCache || !m_renderCache->isValid())
        return;

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
        spine::Color attachmentColor(0, 0, 0, 0);
        spine::Color tint(skeletonColor.r * slotColor.r,
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
            attachmentColor.set(regionAttachment->getColor());

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
            attachmentColor.set(mesh->getColor());
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
#if 0
        // debug drawing
        if(m_debugBones || m_debugSlots || m_debugMesh) {
            m_renderCache->bindShader(RenderCmdsCache::ShaderColor);
            m_renderCache->blendFunc(GL_ONE, GL_ZERO);

            if(m_debugSlots) {
                m_renderCache->drawColor(200, 40, 150, 255);
                m_renderCache->lineWidth(1);
                Point points[4];
                for (size_t i = 0, n = m_skeleton->getSlots().size(); i < n; i++) {
                    auto slot = m_skeleton->getSlots()[i];
                    if(!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(spine::RegionAttachment::rtti))
                        continue;
                    auto* regionAttachment = (spine::RegionAttachment*)slot->getAttachment();
                    regionAttachment->computeWorldVertices(slot->getBone(), m_worldVertices, 0, 2);
                    points[0] = Point(m_worldVertices[0], m_worldVertices[1]);
                    points[1] = Point(m_worldVertices[2], m_worldVertices[3]);
                    points[2] = Point(m_worldVertices[4], m_worldVertices[5]);
                    points[3] = Point(m_worldVertices[6], m_worldVertices[7]);
                    m_renderCache->drawPoly(points, 4);
                }
            }

            if(m_debugMesh) {
                spine::Vector<Point> points;
                m_renderCache->drawColor(40, 150, 200, 255);
                for (size_t i = 0, n = m_skeleton->getSlots().size(); i < n; i++) {
                    auto slot = m_skeleton->getSlots()[i];
                    if(!slot->getAttachment() || !slot->getAttachment()->getRTTI().isExactly(spine::MeshAttachment::rtti))
                        continue;
                    auto* mesh = (spine::MeshAttachment*)slot->getAttachment();
                    size_t numVertices = mesh->getWorldVerticesLength() / 2;
                    points.setSize(numVertices, Point());
                    mesh->computeWorldVertices(*slot,
                                               0,
                                               mesh->getWorldVerticesLength(),
                                               (float*)points.buffer(),
                                               0,
                                               sizeof (Point) / sizeof (float));
                    m_renderCache->drawPoly(points.buffer(), points.size());
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
                    Point p0(bone->getWorldX(), bone->getWorldY());
                    Point p1(x, y);
                    m_renderCache->drawLine(p0, p1);
                }
    //            cache->drawColor(0, 0, 255, 255);
                m_renderCache->pointSize(4.0);
                for(int i = 0, n = m_skeleton->getBones().size(); i < n; i++) {
                    auto bone = m_skeleton->getBones()[i];
                    m_renderCache->drawPoint(Point(bone->getWorldX(), bone->getWorldY()));
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
    emit lightChanged(m_light);
}

bool SpineItem::debugMesh() const
{
    return m_debugMesh;
}

void SpineItem::setDebugMesh(bool debugMesh)
{
    m_debugMesh = debugMesh;
    emit debugMeshChanged(m_debugMesh);
}

int SpineItem::blendColorChannel() const
{
    return m_blendColorChannel;
}

void SpineItem::setBlendColorChannel(int blendColorChannel)
{
    m_blendColorChannel = blendColorChannel;
    emit blendColorChannelChanged(m_blendColorChannel);
}

MyColor SpineItem::blendColor() const
{
    return m_blendColor;
}

void SpineItem::setBlendColor(const MyColor &color)
{
    m_blendColor = color;
    emit blendColorChanged(color);
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

qreal SpineItem::scaleY() const
{
    return m_scaleY;
}

void SpineItem::setScaleY(const qreal &value)
{
    m_scaleY = value;
    if(isSkeletonReady())
        m_skeleton->setScaleY(m_scaleY * m_skeletonScale);
    emit scaleYChanged(m_scaleY);
}

qreal SpineItem::scaleX() const
{
    return m_scaleX;
}

void SpineItem::setScaleX(const qreal &value)
{
    m_scaleX = value;
    if(isSkeletonReady())
        m_skeleton->setScaleX(m_scaleX * m_skeletonScale);
    emit scaleXChanged(m_scaleX);
}

qreal SpineItem::defaultMix() const
{
    return m_defaultMix;
}

void SpineItem::setDefaultMix(const qreal &defaultMix)
{
    m_defaultMix = defaultMix;
    emit defaultMixChanged(m_defaultMix);
    if(isSkeletonReady()) {
        m_animationStateData->setDefaultMix(m_defaultMix);
        return;
    }
    else{
        //m_lazyLoadTimer->stop();
        //m_lazyLoadTimer->start();
    }
}

qreal SpineItem::timeScale() const
{
    return m_timeScale;
}

void SpineItem::setTimeScale(const qreal &timeScale)
{
    m_timeScale = timeScale;
    emit timeScaleChanged(m_timeScale);
}

qreal SpineItem::skeletonScale() const
{
    return m_skeletonScale;
}

void SpineItem::setSkeletonScale(const qreal &skeletonScale)
{
    if(m_isLoading)
        return;
    m_skeletonScale = skeletonScale;
    if(isSkeletonReady()) {
        m_skeleton->setScaleX(m_scaleX * m_skeletonScale);
        m_skeleton->setScaleY(m_scaleY * m_skeletonScale);
    }
    emit skeletonScaleChanged(m_skeletonScale);
}

QStringList SpineItem::animations() const
{
    return m_animations;
}

QStringList SpineItem::skins() const
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
    emit debugSlotsChanged(m_debugSlots);
}

bool SpineItem::debugBones() const
{
    return m_debugBones;
}

void SpineItem::setDebugBones(bool debugBones)
{
    m_debugBones = debugBones;
    emit debugBonesChanged(m_debugBones);
}

bool SpineItem::loaded() const
{
    return m_loaded;
}

QSize SpineItem::sourceSize() const
{
    return m_sourceSize;
}

void SpineItem::setSourceSize(const QSize &sourceSize)
{
    m_sourceSize = sourceSize;
    emit sourceSizeChanged(m_sourceSize);
}

void SpineItem::updateBoundingRect()
{
    setSourceSize(QSize(m_boundingRect.width(), m_boundingRect.height()));
    /*if(m_hasViewPort)
        setImplicitSize(m_viewPortRect.width(), m_viewPortRect.height());
    else
        setImplicitSize(m_boundingRect.width(), m_boundingRect.height());*/
}

void SpineItem::onCacheRendered()
{
    if(m_requestDestroy)
        return;
    updateSkeletonAnimation();
}

void SpineItem::onVisibleChanged()
{
    if(isSkeletonReady() && isVisible())
        emit animationUpdated();
}

bool SpineItem::isSkeletonReady() const
{
    return m_loaded && m_atlas && m_skeleton && m_animationState;
}

SpineItemWorker::SpineItemWorker(SpineItem *spItem) :
    m_spItem(spItem)
{

}

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

void SpineItemWorker::setAnimation(int trackIndex, const MyString &name, bool loop)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    if(!contains(m_spItem->m_animations, name)) {
        return;
    }
    m_spItem->m_animationState->setAnimation(size_t(trackIndex), convert(name), loop);
    m_spItem->m_timer.setBaseTime(0);
}

void SpineItemWorker::addAnimation(int trackIndex, const MyString &name, bool loop, float delay)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    if(!contains(m_spItem->m_animations, name)) {
        return;
    }
    m_spItem->m_animationState->addAnimation(size_t(trackIndex), convert(name), loop, delay);
	m_spItem->m_timer.setBaseTime(0);
}

void SpineItemWorker::setToSetupPose()
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_skeleton->setToSetupPose();
    m_spItem->m_animationState->apply(*m_spItem->m_skeleton.get());
    m_spItem->m_skeleton->updateWorldTransform();
}

void SpineItemWorker::setBonesToSetupPose()
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_skeleton->setBonesToSetupPose();
}

void SpineItemWorker::setSlotsToSetupPose()
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_skeleton->setSlotsToSetupPose();
}

void SpineItemWorker::setAttachment(const MyString &slotName, const MyString &attachmentName)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_skeleton->setAttachment(convert(slotName), convert(attachmentName));
}

void SpineItemWorker::setMix(const MyString &fromAnimation, const MyString &toAnimation, float duration)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_animationStateData->setMix(convert(fromAnimation),
								convert(toAnimation),
                                 duration);
}

void SpineItemWorker::setSkin(const MyString &skinName)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    if(!contains(m_spItem->m_skins, skinName)) {
    }
    m_spItem->m_skeleton->setSkin(convert(skinName));
}

void SpineItemWorker::clearTracks()
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_animationState->clearTracks();
    m_spItem->m_animating = false;
}

void SpineItemWorker::clearTrack(int trackIndex)
{
    if(!m_spItem->isSkeletonReady()) {
        return;
    }
    m_spItem->m_animationState->clearTrack(size_t(trackIndex));
    if(m_spItem->m_animationState->getTracks().size() <= 0)
        m_spItem->m_animating = false;
}
