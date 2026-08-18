#include "AudioManager.h"
#include "raylib.h"

void AudioManager::init()
{
}

void AudioManager::update()
{
    for (auto& [id, music] : m_music)
    {
        UpdateMusicStream(music);
    }
}

void AudioManager::loadSound(const std::string& id, const std::string& path)
{
}

void AudioManager::playSound(const std::string& id)
{
}

void AudioManager::stopSound(const std::string& id)
{
}

void AudioManager::loadMusic(const std::string& id, const std::string& path)
{
}

void AudioManager::playMusic(const std::string& id)
{
}

void AudioManager::stopMusic(const std::string& id)
{
}


void AudioManager::setMasterVolume()
{
}

void AudioManager::setSoundVolume()
{
}

void AudioManager::setMusicVolume()
{
}

void AudioManager::shutdown()
{
}
