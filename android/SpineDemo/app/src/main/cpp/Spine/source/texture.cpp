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

#ifdef WIN32
#include <GL/glew.h>
#elif defined __ANDROID__
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#elif defined __APPLE__
#include <OpenGLES/ES3/glext.h>
#else
#error "platform unknown"
#endif

#include <unistd.h>
#include "texture.h"
#include <spine/Extension.h>
#include "MyTexture.h"

AimyTextureLoader::AimyTextureLoader()
{

}

AimyTextureLoader::~AimyTextureLoader()
{
    releaseTextures();
}

void AimyTextureLoader::load(spine::AtlasPage &page, const spine::String &path)
{
	std::string filePath(path.buffer());

    if(m_textureHash.find(filePath) != m_textureHash.end()) {
        auto tex = m_textureHash[filePath];
		tex->AddRef();
        page.setRendererObject(tex.get());
        return;
    }

    if(0 != access(filePath.c_str(), F_OK)) {
        return;
    }
	std::shared_ptr<Texture> tex = std::shared_ptr<Texture>(new Texture(filePath));
    tex->AddRef();
	mTextureSet.insert(tex.get());//保存指针，用于验证外部传入合法性
	std::shared_ptr<MyTexture> myTexture(new MyTexture(filePath.c_str()));
	m_glTextureHash.insert(std::make_pair(tex->name, myTexture));

    page.setRendererObject(tex.get());
    m_textureHash.insert(std::make_pair(filePath, tex));
}

void AimyTextureLoader::unload(void *texture)
{
	do{
		auto iterTex = mTextureSet.find(texture);
		if (iterTex == mTextureSet.end()){
			assert(false);
			break;
		}
		Texture *tex = reinterpret_cast<Texture*>(texture);
		auto iter = m_textureHash.find(tex->name);
		if (iter == m_textureHash.end()){
			assert(false);
			break;
		}
		int ref = iter->second->Release();
		if (ref > 0){
			break;
		}
		m_glTextureHash.erase(tex->name);
		m_textureHash.erase(iter);
		mTextureSet.erase(iterTex);
	}while (false);
}

std::shared_ptr<MyTexture> AimyTextureLoader::getGLTexture(Texture *texture)
{
	auto iterTex = mTextureSet.find(texture);
	if (iterTex == mTextureSet.end()){
		assert(false);
		return nullptr;
	}
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
	assert(mTextureSet.empty());
	m_glTextureHash.clear();
	m_textureHash.clear();
	mTextureSet.clear();
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

