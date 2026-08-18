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

	void loadSound(const std::string& id, const std::string& path);
	void playSound(const std::string& id);
	void stopSound(const std::string& id);

	void loadMusic(const std::string& id, const std::string& path);
	void playMusic(const std::string& id);
	void stopMusic(const std::string& id);

	void setMasterVolume();
	void setSoundVolume();
	void setMusicVolume();

private:
	std::unordered_map<std::string, Sound> m_sounds;
	std::unordered_map<std::string, Music> m_music;

};

