/*
 * AudioEngine.h
 *
 *  Created on: Jun 4, 2017
 *      Author: Simon
 */

#ifndef AUDIOENGINE_H_
#define AUDIOENGINE_H_

#include "/Library/Frameworks/SDL2_mixer.framework/Headers/SDL_Mixer.h"
#include <string>
#include "Cache.h"

namespace Engine {

class SoundEffect {
public:
	//here 0 is play once, 1 is repeat once
	void play(int loops = 0);
	friend class AudioEngine;
private:
	Mix_Chunk* _chunk = nullptr;
	static int _currentChannel;

};

class Music {
public:
	//for some reason 1 is play once
	void play(int loops = -1);

	static void pause();
	static void stop();
	static void resume();
	friend class AudioEngine;
private:
	Mix_Music* _music = nullptr;
};

class AudioEngine {
public:
	AudioEngine();
	virtual ~AudioEngine();

	void init();
	void destroy();

	SoundEffect loadSoundEffect(const std::string& path);
	Music loadMusic(const std::string& path);
private:
	bool initialized = false;

	Cache<Mix_Chunk*> _effectCache;
	Cache<Mix_Music*> _musicCache;
};

} /* namespace Engine */

#endif /* AUDIOENGINE_H_ */
