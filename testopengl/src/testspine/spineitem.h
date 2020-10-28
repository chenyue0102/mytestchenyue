#ifndef SPINEITEM_H
#define SPINEITEM_H
#include <memory>
#include <functional>

#include "rendercmdscache.h"
#include "My/BaseTime.h"

class SpineItemWorker;

class RenderCmdsCache;
class AimyTextureLoader;
class Texture;
class SpineVertexEffect;
class SkeletonRenderer;

namespace spine {
class Atlas;
class SkeletonJson;
class SkeletonData;
class AnimationStateData;
class AnimationState;
class Skeleton;
class Attachment;
class SkeletonClipping;
class Slot;
}

struct RenderCmdBatch{
	std::vector<SpineVertex> vertices;
	std::vector<GLushort> triangles;
    Texture* texture = nullptr;
    int blendMode;
};

struct Size {
	Size(int _w, int _h) :w(_w), h(_h) {

	}
	Size() :w(), h() {

	}

	int w, h;
};


typedef spine::Color MyColor;
typedef std::string MyString;
typedef Size MySize;
#define qreal float
#define QStringList std::vector<std::string>
typedef long long qint64;


class SpineItem
{
public:
    explicit SpineItem();
    ~SpineItem();
public:
	void setAtlasFile(const std::string &atlasPath);
	void setSkeletonFile(const std::string &skeletonPath);
	bool create();


	bool isVisible() { return true; }

    /**
     * @brief setToSetupPose Affect after clearTracks() has been invoked.
     */
    void setToSetupPose();
    /**
     * @brief setBonesToSetupPose Affect after clearTracks() has been invoked.
     */
    void setBonesToSetupPose();
    /**
     * @brief setSlotsToSetupPose Affect after clearTracks() has been invoked.
     */
    void setSlotsToSetupPose();
    /**
     * @brief setAttachment Dynaimicly change attachment for a slot.
     * @param slotName
     * @param attachmentName
     * @return
     */
    bool setAttachment(const MyString& slotName, const MyString& attachmentName);
    /**
     * @brief setMix Animation mixing duration.
     * @param fromAnimation
     * @param toAnimation
     * @param duration
     */
    void setMix(const MyString& fromAnimation, const MyString& toAnimation, float duration);
    /**
     * @brief setAnimation Sets the current animation for a track, discarding any queued animations.
     * A track entry to allow further customization of animation playback. References to the track entry must not be kept after AnimationState.Dispose.
     * @param trackIndex
     * @param name
     * @param loop If true, the animation will repeat.If false, it will not, instead its last frame is applied if played beyond its duration. In either case TrackEntry.TrackEnd determines when the track is cleared.
     */
    void setAnimation (int trackIndex, const MyString& name, bool loop);
    /**
     * @brief addAnimation Queues an animation by name.
     * @param trackIndex
     * @param name
     * @param loop
     * @param delay
     */
    void addAnimation (int trackIndex, const MyString& name, bool loop, float delay = 0);
    /**
     * @brief setSkin Changes skin by specified skin name at anytime.
     * @param skinName
     */
    void setSkin(const MyString& skinName);
    /**
     * @brief clearTracks Clears all animation tracks, and keeps last rendered frame pixels, and after then you can invoke setToSetupPose to rollback firstly orignal frame immediately.
     */
    void clearTracks ();
    /**
     * @brief clearTrack Clear specfied animation track by given track id.
     * @param trackIndex
     */
    void clearTrack(int trackIndex = 0);

    friend class SpineItemWorker;
    friend class SkeletonRenderer;

    friend void animationSateListioner(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

    

    bool isSkeletonReady() const;

	MySize sourceSize() const;
    void setSourceSize(const MySize &sourceSize);

    bool loaded() const;

    bool debugBones() const;
    void setDebugBones(bool debugBones);

    bool debugSlots() const;
    void setDebugSlots(bool debugSlots);

    QStringList vailableAnimations() const;
	QStringList vailableSkins() const;

	QStringList animations() const;
	QStringList skins() const;

    qreal skeletonScale() const;
    void setSkeletonScale(const qreal &skeletonScale);

    int fps() const;
    void setFps(int fps);

    qreal timeScale() const;
    void setTimeScale(const qreal &timeScale);

    qreal defaultMix() const;
    void setDefaultMix(const qreal &defaultMix);

    qreal scaleX() const;
    void setScaleX(const qreal &value);

    qreal scaleY() const;
    void setScaleY(const qreal &value);

    /*QObject *vertexEfect() const;
    void setVertexEfect(QObject *vertexEfect);*/

	MyColor blendColor() const;
    void setBlendColor(const MyColor &color);

    int blendChannel() const;
    void setBlendChannel(int blendChannel);

    int blendColorChannel() const;
    void setBlendColorChannel(int blendColorChannel);

    bool debugMesh() const;
    void setDebugMesh(bool debugMesh);

    float light() const;
    void setLight(float light);

    bool asynchronous() const;
    void setAsynchronous(bool asynchronous);

public://signals:

    // property signals
	void atlasFileChanged(const MyString& path) {};
    void skeletonFileChanged(const MyString& path) {};
    void isSkeletonReadyChanged(const bool& ready) {};
    void sourceSizeChanged(const MySize& size) {};
    void loadedChanged(const bool& loaded) {};
    void premultipliedAlphaChanged(const bool& ret) {};
    void debugBonesChanged(const bool& ret) {};
    void debugSlotsChanged(const bool& ret) {};
    void debugMeshChanged(const bool& ret) {};
    void animationsChanged(const QStringList& animations) {};
    void skinsChanged(const QStringList& skins) {};
    void skeletonScaleChanged(const qreal& scale) {};
    void fpsChanged(const int& fps) {};
    void timeScaleChanged(const qreal& timesCale) {};
    void defaultMixChanged(const qreal& defaultMix) {};
    void scaleXChanged(const qreal& scaleX) {};
    void scaleYChanged(const qreal& scaleY) {};
    void vertexEfectChanged() {};
    void animationUpdated() {};
    void blendColorChanged(const MyColor& color) {};
    void resourceLoadFailed() {};
    void blendColorChannelChanged(const int& channel) {};
    void lightChanged(const float& light) {};

    // rumtime signals
    void animationStarted(int trackId, MyString animationName) {};
    void animationCompleted(int trackId, MyString animationName) {};
    void animationInterrupted(int trackId, MyString animationName) {};
    void animationEnded(int trackId, MyString animationName) {};
    void animationDisposed(int trackId, MyString animationName) {};
    void cacheRendered() {};
    void resourceReady() {};

private:
    void updateBoundingRect();
    void onCacheRendered();
    void onVisibleChanged();

public:
    void updateSkeletonAnimation();
    RectF computeBoundingRect();
    Texture* getTexture(spine::Attachment* attachment) const;
    void releaseSkeletonRelatedData();
    bool nothingToDraw(spine::Slot& slot);
    void batchRenderCmd(RenderCmdsCache *render);
    void renderToCache(RenderCmdsCache *render);

private:
	std::string m_atlasFile;
	std::string m_skeletonFile;


    bool m_loaded = false;
    bool m_debugBones = false;
    bool m_debugSlots = false;
    bool m_debugMesh = false;
    bool m_isLoading = false;
    bool m_hasViewPort = false;
    bool m_animating = false;
    qreal m_scaleX = 1.0;
    qreal m_scaleY = 1.0;
    qreal m_timeScale = 1.0;
    float m_light = 1.0;
    qreal m_defaultMix = 0.1;
    MySize m_sourceSize;
    float* m_worldVertices;
    bool m_shouldReleaseCacheTexture = false;
    qreal m_skeletonScale;
	QStringList m_animations;
	QStringList m_skins;
    RectF m_boundingRect;
    RectF m_viewPortRect;
    BaseTime m_timer;
	std::shared_ptr<spine::Atlas> m_atlas;
	std::shared_ptr<spine::SkeletonData> m_skeletonData;
	std::shared_ptr<spine::AnimationStateData> m_animationStateData;
	std::shared_ptr<spine::AnimationState> m_animationState;
	std::shared_ptr<spine::Skeleton> m_skeleton;
	std::shared_ptr<spine::SkeletonClipping> m_clipper;
    SpineVertexEffect* m_vertexEfect = nullptr;
	std::shared_ptr<SpineItemWorker> m_spWorker;
	MyColor m_blendColor;
    int m_blendColorChannel = -1;
    bool m_requestDestroy = false;
    std::vector<RenderCmdBatch> m_batches;
    bool m_requestRender = false;
	int m_fadecounter = 1; // make sure last state textue has been render.
};

class SpineItemWorker{
public:
    SpineItemWorker(SpineItem* spItem = nullptr);

public:
    void setAnimation (int trackIndex, const MyString& name, bool loop);
    void addAnimation (int trackIndex, const MyString& name, bool loop, float delay = 0);
    void setToSetupPose();
    void setBonesToSetupPose();
    void setSlotsToSetupPose();
    void setAttachment(const MyString& slotName, const MyString& attachmentName);
    void setMix(const MyString& fromAnimation, const MyString& toAnimation, float duration);
    void setSkin(const MyString& skinName);
    void clearTracks ();
    void clearTrack(int trackIndex = 0);

private:
    SpineItem* m_spItem = nullptr;
};

#endif // SPINEITEM_H
