#ifndef GWSOUNDMANAGER_H
#define GWSOUNDMANAGER_H
#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>
#include <stdio.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace GW {
    class SoundManager {
    public:
        SoundManager ();
        virtual ~SoundManager ();
        static void init();
        static void pleerCreation(AAssetManager * aassetMgr);
    private:
    };
} /* GW */

#endif //GWSOUNDMANAGER_H
