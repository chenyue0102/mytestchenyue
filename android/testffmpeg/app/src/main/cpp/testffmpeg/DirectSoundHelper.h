#ifndef _DIRECT_SOUND_HELPER_H_
#define _DIRECT_SOUND_HELPER_H_
#include <stdint.h>
#include <dsound.h>

class DirectSoundHelper
{
public:
	DirectSoundHelper();
	~DirectSoundHelper();
public:
	bool init();
	bool destroy();
private:
	IDirectSound8 *mIDirectSound8;
};


#endif