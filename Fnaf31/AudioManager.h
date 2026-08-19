#pragma once
#include <unordered_map>
#include <string>
#include "raylib.h"	

class AudioManager
{
public:
	void init();
	void update();
	void shutdown();

	bool loadSound(const std::string& id, const std::string& path);
	void playSound(const std::string& id);
	void stopSound(const std::string& id);

	bool loadMusic(const std::string& id, const std::string& path);
	void playMusic(const std::string& id);
	void stopMusic(const std::string& id);

	void setMasterVolume(float volume);
	void setSoundVolume(float volume);
	void setMusicVolume(float volume);

private:
	std::unordered_map<std::string, Sound> m_sounds;
	std::unordered_map<std::string, Music> m_music;

	bool m_initialized = false;

};

