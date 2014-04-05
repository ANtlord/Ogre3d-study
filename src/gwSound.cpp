#include "../include/gwSound.h"
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SOUND", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "SOUND", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "SOUND", __VA_ARGS__))
using namespace std;
namespace GW {

AAssetManager * Sound::_aassetMgr = NULL;
SLObjectItf Sound::outputMixObj;

Sound::Sound (const string &filename, AAssetManager * aassetMgr) : _filename(filename)
{
    if (Sound::_aassetMgr == NULL) Sound::_aassetMgr = aassetMgr;
    baseSound();
}

Sound::Sound(const string &filename) : _filename(filename)
{
    baseSound();
}

void Sound::baseSound()
{
    // Initilization.
    SLObjectItf engineObj;
    const SLInterfaceID pIDs[1] = {SL_IID_ENGINE};
    const SLboolean pIDsRequired[1]  = {true};
    SLresult result = slCreateEngine(
        &engineObj, /* Pointer to result object. */
        0, /* Num of items in array of optional options. */
        NULL, /* Массив дополнительных опций, NULL, если они Вам не нужны */
        1, /*Количество интерфесов, которые должен будет поддерживать создаваемый объект*/
        pIDs, /*Массив ID интерфейсов*/
        pIDsRequired /*Массив флагов, указывающих, необходим ли соответствующий
                       интерфейс. Если указано SL_TRUE, а интерфейс не
                       поддерживается, вызов завершится неудачей, с кодом
                       возврата SL_RESULT_FEATURE_UNSUPPORTED*/
    );
    /*Проверяем результат. Если вызов slCreateEngine завершился неуспехом – ничего не поделаешь*/
    if(result != SL_RESULT_SUCCESS){
        LOGE("Error after slCreateEngine");
        return;
    }
    /*Вызов псевдометода. Первым аргументом всегда идет аналог this*/
    result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE); //Реализуем объект в синхронном режиме
    if(result != SL_RESULT_SUCCESS) {
        LOGE("Error after Realize engineObj");
        return;
    }

    result = (*engineObj)->GetInterface(
        engineObj,  /*this*/
        SL_IID_ENGINE, /*ID интерфейса*/
         &_engine /*Куда поместить результат*/
    );

    const SLInterfaceID pOutputMixIDs[] = {};
    const SLboolean pOutputMixRequired[] = {};
    /*Аналогично slCreateEngine()*/
    result = (*_engine)->CreateOutputMix(_engine, &outputMixObj, 0,
            pOutputMixIDs, pOutputMixRequired);
    result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);
}

ResourseDescriptor Sound::loadResourceDescriptor()
{
    if (_aassetMgr == NULL) LOGE("aassetMgr == NULL");
    AAsset* asset = AAssetManager_open(_aassetMgr, _filename.c_str(), AASSET_MODE_UNKNOWN);
    ResourseDescriptor resourceDescriptor;
    if (asset == NULL) LOGE("asset == NULL");
    resourceDescriptor.descriptor = AAsset_openFileDescriptor(asset,
            &resourceDescriptor.start, &resourceDescriptor.length);
    AAsset_close(asset);
    return resourceDescriptor;
}

bool Sound::play()
{
    ResourseDescriptor resourseDescriptor = loadResourceDescriptor();
    SLDataLocator_AndroidFD locatorIn = {
        SL_DATALOCATOR_ANDROIDFD,
        resourseDescriptor.descriptor,
        resourseDescriptor.start,
        resourseDescriptor.length
    };

    SLDataFormat_MIME dataFormat = {
        SL_DATAFORMAT_MIME,
        NULL,
        SL_CONTAINERTYPE_UNSPECIFIED
    }; 
    SLDataSource audioSrc = {&locatorIn, &dataFormat};

    SLDataLocator_OutputMix dataLocatorOut = {
        SL_DATALOCATOR_OUTPUTMIX,
        outputMixObj
    };

    SLPlayItf player;
    SLDataSink audioSnk = {&dataLocatorOut, NULL};
    const SLInterfaceID pIDs[1] = {SL_IID_PLAY};
    const SLboolean pIDsRequired[1] = {SL_BOOLEAN_TRUE};
    LOGI("pleerCreation player creating");

    // Final actions :)
    SLresult result = (*_engine)->CreateAudioPlayer(_engine, &_playerObj,
            &audioSrc, &audioSnk, 1, pIDs, pIDsRequired);
    if (result != SL_RESULT_SUCCESS) {
        LOGE("error play sound after creation audio player");
        return false;
    }

    result = (*_playerObj)->Realize(_playerObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) {
        LOGE("error play sound after trying play sound");
        return false;
    }

    result = (*_playerObj)->GetInterface(_playerObj, SL_IID_PLAY, &player);
    if (result != SL_RESULT_SUCCESS) {
        LOGE("error play sound after getting interface");
        return false;
    }

    result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) {
        LOGE("error play sound after setting play state");
        return false;
    }
    return true;
}

Sound::~Sound() 
{
    (*_playerObj)->Destroy(_playerObj);
}

} /* GW */
