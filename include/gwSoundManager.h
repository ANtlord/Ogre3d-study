#ifndef GWSOUNDMANAGER_H
#define GWSOUNDMANAGER_H
#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>
#include <stdio.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace GW {
    struct ResourseDescriptor
    {
        int32_t descriptor;
        off_t start;
        off_t length;
    };

    class SoundManager {
    public:
        static ResourseDescriptor loadResourceDescriptor(const char* path);
        SoundManager ();
        virtual ~SoundManager ();
        static void init();
        static void pleerCreation();
    private:
    };
} /* GW */

#endif //GWSOUNDMANAGER_H
