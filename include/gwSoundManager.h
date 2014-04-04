#ifndef GWSOUNDMANAGER_H
#define GWSOUNDMANAGER_H
#include <map>
#include <jni.h>
#include <errno.h>
#include <string>
#include "gwSound.h"
#include <android_native_app_glue.h>
#include <stdio.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>


namespace GW {
/**
SoundManager
@brief Class for managing sounds.
@detailed Class stores set of sounds. It can add to store, get from it and
delete sound from store and from memory.
*/
    class SoundManager {
    public:
    /**
    @brief Method for getting object of manager.
    @return Single objects of GW::SoundManager. 
    */
        inline static SoundManager*	getSingleton();

    /**
    @brief Method gets sound object from store by key.
    @param Key for access.
    @return Instance of class GW::Sound
    */
        Sound * getSound(std::string key) const;

    /**
    @brief Method adds sound object to store.
    @param key Key for access. sound Pointer to sound object for store.
    @return false, if gets errors during of addition. If true, then method was
    successful.
    */
        bool addSound(std::string key, Sound * sound);

    /**
    @brief Method remove sound object from store and delete object from memory.
    @param key Key for access. sound Pointer to sound object for store.
    @return false, if gets errors during of removing. If true, then method was
    successful.
    */
        bool removeSound(std::string key);

    protected:
    /**
    @brief Constructor.
    */
        SoundManager();

    private:
    /**
     @brief Pointer to general instance.
     @detailed Point to general instance, can be accessed by method getSingleton().
    */
        static SoundManager * _self;

    /**
     @brief Store of objects.
     @detailed Container storing sound objects by string value.
    */
        std::map <std::string, Sound*> _sounds;
        
    };
} /* GW */

#endif //GWSOUNDMANAGER_H
