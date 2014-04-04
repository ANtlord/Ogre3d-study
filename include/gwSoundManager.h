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
    class SoundManager {
    public:
        inline static SoundManager*	getSingleton();
        Sound * getSound(std::string key) const;
        bool addSound(std::string key, Sound * sound);
        bool removeSound(std::string key);
    protected:
        SoundManager();
    private:
        static SoundManager * _self;
        std::map <std::string, Sound*> _sounds;
        
    };
} /* GW */

#endif //GWSOUNDMANAGER_H
