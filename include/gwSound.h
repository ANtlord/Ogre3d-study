#ifndef GWSOUND_H
#define GWSOUND_H
#include <string>
#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>
#include <stdio.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>


namespace GW {
    class ResourseDescriptor
    {
        public:
            int32_t descriptor;
            off_t start;
            off_t length;
    };


    class Sound {
    public:
        Sound(const std::string &filename, AAssetManager * aassetMgr);
        Sound(const std::string &filename);
        bool play();
        virtual ~Sound();

    protected:
        static SLObjectItf outputMixObj;

    private:
        void baseSound();
        ResourseDescriptor loadResourceDescriptor();
        static AAssetManager * _aassetMgr;
        const std::string _filename;
        SLEngineItf _engine;
        SLObjectItf _playerObj;
    };
    
} /* GW */

#endif //GWSOUND_H
