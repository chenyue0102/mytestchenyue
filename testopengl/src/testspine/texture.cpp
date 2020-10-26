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

#include <GL/glew.h>

#include "texture.h"

#include <io.h>
#include <spine/Extension.h>
#include "My/MyTexture.h"

AimyTextureLoader::AimyTextureLoader()
{

}

AimyTextureLoader::~AimyTextureLoader()
{
    releaseTextures();
}

AimyTextureLoader *AimyTextureLoader::instance()
{
    static AimyTextureLoader _instance;
    return &_instance;
}

void AimyTextureLoader::load(spine::AtlasPage &page, const spine::String &path)
{
    std::lock_guard<std::mutex> locker(m_mutex);
	std::string filePath(path.buffer());

    if(m_textureHash.find(filePath) != m_textureHash.end()) {
        auto tex = m_textureHash[filePath];
        page.setRendererObject(tex.get());
        return;
    }

    if(0 != _access(filePath.c_str(), 0)) {
        return;
    }
	std::shared_ptr<Texture> tex = std::shared_ptr<Texture>(new Texture(filePath));
	MyTexture *myTexture = new MyTexture(filePath.c_str());
	m_glTextureHash.insert(std::make_pair(tex->name, myTexture));

    page.setRendererObject(tex.get());
    m_textureHash.insert(std::make_pair(filePath, tex));
}

void AimyTextureLoader::unload(void *texture)
{
    
}

MyTexture* AimyTextureLoader::getGLTexture(Texture *texture)
{
    if (!texture || texture->name.empty()) {
        return nullptr;
    }

	if (m_glTextureHash.find(texture->name) != m_glTextureHash.end())
		return m_glTextureHash[texture->name];
	else
		return nullptr;
}

void AimyTextureLoader::releaseTextures()
{
    if (m_glTextureHash.empty())
        return;

    
	for (auto &item : m_glTextureHash) {
		delete item.second;
	}

    m_glTextureHash.clear();
}

AimyExtension::AimyExtension(): spine::DefaultSpineExtension()
{

}

AimyExtension::~AimyExtension()
{

}

char *AimyExtension::_readFile(const spine::String &path, int *length)
{
	char *data;
	FILE *file = fopen(path.buffer(), "rb");
	if (!file) return 0;

	fseek(file, 0, SEEK_END);
	*length = (int)ftell(file);
	fseek(file, 0, SEEK_SET);

	data = (char*)malloc(*length);
	fread(data, 1, *length, file);
	fclose(file);

	return data;
}

spine::SpineExtension* spine::getDefaultExtension() {
    return new AimyExtension();
}

