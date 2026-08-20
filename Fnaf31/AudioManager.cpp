#include "AudioManager.h"
#include "raymath.h"

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

void AudioManager::playLoopingSound(const std::string& id)
{
    const auto it = m_sounds.find(id);

    if (it == m_sounds.end())
    {
        return;
    }

    //m_loopingSounds.insert(id);

    if (!IsSoundPlaying(it->second))
    {
        PlaySound(it->second);
    }
}

void AudioManager::stopLoopingSound(const std::string& id)
{
    const auto it = m_sounds.find(id);

    if (it == m_sounds.end())
    {
        return;
    }

    //m_loopingSounds.erase(id);

    StopSound(it->second);
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


void AudioManager::setMasterVolume(float volume)
{
    volume = Clamp(volume, 0.0f, 1.0f);

    SetMasterVolume(volume);
}
void AudioManager::setSoundVolume(float volume)
{
}

void AudioManager::setMusicVolume(float volume)
{
}

void AudioManager::shutdown()
{
    if (!m_initialized)
    {
        return;
    }

    for (auto& [id, sound] : m_sounds)
    {
        UnloadSound(sound);
    }

    for (auto& [id, music] : m_music)
    {
        UnloadMusicStream(music);
    }

    m_sounds.clear();
    m_music.clear();

    CloseAudioDevice();

    m_initialized = false;
}

bool AudioManager::isSoundPlaying(
    const std::string& id
) const
{
    const auto it =
        m_sounds.find(id);

    if (it == m_sounds.end())
    {
        return false;
    }

    return IsSoundPlaying(
        it->second
    );
}
