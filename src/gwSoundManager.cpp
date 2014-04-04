#include "../include/gwSoundManager.h"
#include <android/log.h>
#include <OgreArchive.h>
#include <OgreArchiveManager.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SOUND_MANAGER", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "SOUND_MANAGER", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "SOUND_MANAGER", __VA_ARGS__))

using namespace std;

namespace GW {
SoundManager * SoundManager::_self = 0;

inline SoundManager * SoundManager::getSingleton()
{
    if (_self == 0) {
        _self = new SoundManager();
    }
    return _self;
}

/****************************************************************************/
SoundManager::SoundManager()
{
}

/****************************************************************************/

Sound * SoundManager::getSound(string key) const
{
    try {
        return _sounds.at(key);
    } catch (std::out_of_range) {
        return 0;
    }
}

bool SoundManager::addSound(string key, Sound * sound)
{
    if (_sounds.find(key) == _sounds.end()) {  // Value with given key doesn't exists.
        _sounds[key] = sound;
        return true;
    }
    else {  // Value with given key exists. Objects was not added.
        return false;
    }
}

bool SoundManager::removeSound(string key)
{
    if (_sounds.find(key) != _sounds.end()) {  // Value with given key doesn't exists.
        delete _sounds[key];
        _sounds.erase(key);
        return true;
    }
    else {  // Value with given key exists. Objects was not added.
        return false;
    }
}

}
