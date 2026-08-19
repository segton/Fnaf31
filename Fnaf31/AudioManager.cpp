#include "AudioManager.h"
#include "raylib.h"

void AudioManager::init()
{
    if (m_initialized)
    {
        return;
    }

    InitAudioDevice();

    m_initialized = true;
}

void AudioManager::update()
{
    for (auto& [id, music] : m_music)
    {
        UpdateMusicStream(music);
    }
}

bool AudioManager::loadSound(const std::string& id, const std::string& path)
{
    if (m_sounds.find(id) != m_sounds.end())
    {
        return false;
    }

    Sound sound = LoadSound(path.c_str());

    m_sounds.emplace(id, sound);

    return true;
}

void AudioManager::playSound(const std::string& id)
{
    const auto it = m_sounds.find(id);

    if (it == m_sounds.end())
    {
        return;
    }

    PlaySound(it->second);
}

void AudioManager::stopSound(const std::string& id)
{
}

bool AudioManager::loadMusic(const std::string& id, const std::string& path)
{
    if (m_music.find(id) != m_music.end())
    {
        return false;
    }

    Music music =
        LoadMusicStream(path.c_str());

    m_music.emplace(id, music);

    return true;
}

void AudioManager::playMusic(const std::string& id)
{
    const auto it = m_music.find(id);

    if (it == m_music.end())
    {
        return;
    }

    PlayMusicStream(it->second);
}

void AudioManager::stopMusic(const std::string& id)
{
    const auto it = m_music.find(id);

    if (it == m_music.end())
    {
        return;
    }

    StopMusicStream(it->second);
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
