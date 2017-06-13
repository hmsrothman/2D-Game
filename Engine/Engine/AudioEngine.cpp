/*
 * AudioEngine.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: Simon
 */

#include <AudioEngine.h>
#include <Errors.h>
#include "/Library/Frameworks/SDL2_mixer.framework/Headers/SDL_Mixer.h"

namespace Engine {

int SoundEffect::_currentChannel = 0;

void SoundEffect::play(int loops /*=0*/) {
	if (Mix_PlayChannel(_currentChannel++, _chunk, loops) == -1) {
		_currentChannel = 0;
		if (Mix_PlayChannel(_currentChannel++, _chunk, loops) == -1) {
			fatalError("sound effect playing failed");
		}
	}
}

void Music::play(int loops /*=-1*/) {
	if (Mix_PlayMusic(_music, loops) == -1) {
		fatalError("music playing failed");
	}
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::stop() {
	Mix_HaltMusic();
}

void Music::resume() {
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine() {

}

AudioEngine::~AudioEngine() {
	destroy();
}

SoundEffect AudioEngine::loadSoundEffect(const std::string& path) {
	SoundEffect effect;
	effect._chunk = _effectCache.get(path);
	return effect;
}

Music AudioEngine::loadMusic(const std::string& path) {
	Music music;
	music._music = _musicCache.get(path);
	return music;
}

void AudioEngine::init() {
	if (initialized) {
		fatalError("tried to init audio more than once");
	}
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
		fatalError("mix init failed " + std::string(Mix_GetError()));
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)
			== -1) {
		fatalError("mix open audo failed: " + std::string(Mix_GetError()));
	}

	initialized = true;
}

void AudioEngine::destroy() {
	if (initialized) {
		initialized = false;
		for (auto& it : _effectCache) {
			Mix_FreeChunk(it.second);
		}
		for (auto& it : _musicCache) {
			Mix_FreeMusic(it.second);
		}

		_effectCache.clear();
		_musicCache.clear();

		Mix_CloseAudio();
		Mix_Quit();
		initialized = false;
	}

}

} /* namespace Engine */
