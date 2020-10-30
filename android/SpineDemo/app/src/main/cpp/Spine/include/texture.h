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

#ifndef TEXTURE_H
#define TEXTURE_H
#include <map>
#include <set>
#include <mutex>
#include <string>
#include <memory>

#include <spine/spine.h>


struct Texture
{
public:
    explicit Texture(const std::string& _name):name(_name),mRef(0){}

    //简化处理，非原子操作，需要使用者加锁
    int AddRef(){return ++mRef;}
    int Release(){return --mRef;}
public:
	std::string name;
    int mRef;
};

class MyTexture;

/**
 * AimyTextureLoader每个线程使用自己的texture loader
 */
class AimyTextureLoader: public spine::TextureLoader{
public:
    AimyTextureLoader();
    ~AimyTextureLoader() override;

public:
    virtual void load(spine::AtlasPage &page, const spine::String &path) override;
    virtual void unload(void *texture) override;
	std::shared_ptr<MyTexture> getGLTexture(Texture*texture);
    void releaseTextures();

private:
    std::map<std::string, std::shared_ptr<Texture>> m_textureHash;
	std::map<std::string, std::shared_ptr<MyTexture>> m_glTextureHash;
	std::set<void*> mTextureSet;//用于验证外部传入指针合法性
};

class AimyExtension: public spine::DefaultSpineExtension{
public:
    AimyExtension();
    virtual ~AimyExtension() override;

protected:
    virtual char * _readFile(const spine::String &path, int *length) override;
};

#endif // TEXTURE_H
