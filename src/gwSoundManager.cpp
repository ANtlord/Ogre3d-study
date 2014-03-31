#include "../include/gwSoundManager.h"
#include <android/log.h>
#include <OgreArchive.h>
#include <OgreArchiveManager.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SOUND_MANAGER", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "SOUND_MANAGER", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "SOUND_MANAGER", __VA_ARGS__))

namespace GW {

SLEngineItf engine;
SLObjectItf outputMixObj;
/****************************************************************************/
SoundManager::SoundManager()
{
}

/****************************************************************************/
SoundManager::~SoundManager( void )
{
}

/*
 * Method for getting file's description, which has address of start byte in
 * VFS (Virtual File System) and length of this file.
 */
ResourseDescriptor SoundManager::loadResourceDescriptor(const char* path,
        AAssetManager * aassetMgr)
{
    if (aassetMgr == NULL) LOGE("aassetMgr == NULL");
    AAsset* asset = AAssetManager_open(aassetMgr, path, AASSET_MODE_UNKNOWN);
    ResourseDescriptor resourceDescriptor;
    if (asset == NULL) LOGE("asset == NULL");
    resourceDescriptor.descriptor = AAsset_openFileDescriptor(asset,
            &resourceDescriptor.start, &resourceDescriptor.length);
    AAsset_close(asset);
    return resourceDescriptor;
}

void SoundManager::init()
{
    SLObjectItf engineObj;
    const SLInterfaceID pIDs[1] = {SL_IID_ENGINE};
    const SLboolean pIDsRequired[1]  = {true};
    SLresult result = slCreateEngine(
        &engineObj, /*Указатель на результирующий объект*/
        0, /*Количество элементов в массиве дополнительных опций*/
        NULL, /*Массив дополнительных опций, NULL, если они Вам не нужны*/
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
    /*В дальнейшем я буду опускать проверки результата, дабы не загромождать код*/
    if(result != SL_RESULT_SUCCESS){
        LOGE("Error after Realize engineObj");
        return;
    }

    result = (*engineObj)->GetInterface(
        engineObj,  /*this*/
        SL_IID_ENGINE, /*ID интерфейса*/
         &engine /*Куда поместить результат*/
    );

    const SLInterfaceID pOutputMixIDs[] = {};
    const SLboolean pOutputMixRequired[] = {};
    /*Аналогично slCreateEngine()*/
    result = (*engine)->CreateOutputMix(engine, &outputMixObj, 0, pOutputMixIDs, pOutputMixRequired);
    result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);

    LOGI("init finished");
}

void SoundManager::pleerCreation(AAssetManager * aassetMgr)
{
    LOGI("pleerCreation started");
    ResourseDescriptor resourseDescriptor = loadResourceDescriptor("test.ogg", aassetMgr);
    LOGI("pleerCreation file used");

    SLDataLocator_AndroidFD locatorIn = {
        SL_DATALOCATOR_ANDROIDFD,
        resourseDescriptor.descriptor,
        resourseDescriptor.start,
        resourseDescriptor.length
    };
    LOGI("pleerCreation locator created");

    SLDataFormat_MIME dataFormat = {
        SL_DATAFORMAT_MIME,
        NULL,
        SL_CONTAINERTYPE_UNSPECIFIED
    };= 

    SLDataSource audioSrc = {&locatorIn, &dataFormat};

    LOGI("pleerCreation outmix");
    SLDataLocator_OutputMix dataLocatorOut = {
        SL_DATALOCATOR_OUTPUTMIX,
        outputMixObj
    };

    SLPlayItf player;
    SLDataSink audioSnk = {&dataLocatorOut, NULL};
    const SLInterfaceID pIDs[1] = {SL_IID_PLAY};
    const SLboolean pIDsRequired[1] = {SL_BOOLEAN_TRUE};
    SLObjectItf _playerObj;
    LOGI("pleerCreation player creating");
    SLresult result = (*engine)->CreateAudioPlayer(engine, &_playerObj,
            &audioSrc, &audioSnk, 1, pIDs, pIDsRequired);
    if (result != SL_RESULT_SUCCESS) LOGE("error after creation audio player");

    result = (*_playerObj)->Realize(_playerObj, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) LOGE("error after trying play sound");

    result = (*_playerObj)->GetInterface(_playerObj, SL_IID_PLAY, &player);
    result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
}

}

