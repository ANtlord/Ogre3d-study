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

/*Вновь используем AAssetManager*/
ResourseDescriptor SoundManager::loadResourceDescriptor(const char* path, AAssetManager * aassetMgr)
{
    FILE * f = fopen(path, "r");
    //Ogre::ArchiveManager *mgr = Ogre::ArchiveManager::getSingletonPtr();
    //Ogre::ArchiveManager::ArchiveMapIterator archIter = mgr->getArchiveIterator();
    //bool flag = archIter.begin()->second->exists(path);

    //if (f != NULL) {
        //LOGI("FILE IS EXIST.");
    //}
    //else {
        //LOGI("FILE DOESN'T EXIST.");
    //}
    if (aassetMgr == NULL) 
        LOGI("aassetMgr == NULL");

    AAsset* asset = AAssetManager_open(aassetMgr, path, AASSET_MODE_UNKNOWN);
    LOGI("123");
    ResourseDescriptor resourceDescriptor;
    LOGI("456");
    if (asset == NULL) 
        LOGI("asset == NULL");
    resourceDescriptor.descriptor = AAsset_openFileDescriptor(asset,
            &resourceDescriptor.start, &resourceDescriptor.length);
    LOGI("789");
    AAsset_close(asset);
    LOGI("0");
    return resourceDescriptor;
}

void SoundManager::init()
{
    LOGI("init started");
    SLObjectItf engineObj;
    const SLInterfaceID pIDs[1] = {SL_IID_ENGINE};
    const SLboolean pIDsRequired[1]  = {true};
    SLresult result = slCreateEngine(
        &engineObj, /*Указатель на результирующий объект*/
        0, /*Количество элементов в массиве дополнительных опций*/
        NULL, /*Массив дополнительных опций, NULL, если они Вам не нужны*/
        1, /*Количество интерфесов, которые должен будет поддерживать создаваемый объект*/
        pIDs, /*Массив ID интерфейсов*/
    pIDsRequired /*Массив флагов, указывающих, необходим ли соответствующий интерфейс. Если указано SL_TRUE, а интерфейс не поддерживается, вызов завершится неудачей, с кодом возврата SL_RESULT_FEATURE_UNSUPPORTED*/
    );

    /*Проверяем результат. Если вызов slCreateEngine завершился неуспехом – ничего не поделаешь*/
    if(result != SL_RESULT_SUCCESS){
        LOGE("Error after slCreateEngine");
        return;
    }

    /*Вызов псевдометода. Первым аргументом всегда идет аналог this*/
    result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE); //Реализуем объект  в синхронном режиме
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
    //ResourseDescriptor resourseDescriptor = loadResourceDescriptor("/storage/emulated/0/Alarms/10_Rise From The Sea Of Flames.mp3", aassetMgr);
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
    };

    SLDataSource audioSrc = {&locatorIn, &dataFormat};

    LOGI("pleerCreation outmix");
    SLDataLocator_OutputMix dataLocatorOut = {
        SL_DATALOCATOR_OUTPUTMIX,
        outputMixObj
    };

    SLDataSink audioSnk = {&dataLocatorOut, NULL};
    const SLInterfaceID pIDs[2] = {SL_IID_PLAY, SL_IID_SEEK};
    const SLboolean pIDsRequired[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    SLObjectItf playerObj;
    LOGI("pleerCreation player creating");
    SLresult result = (*engine)->CreateAudioPlayer(engine, &playerObj, &audioSrc, &audioSnk, 2, pIDs, pIDsRequired);

    LOGI("pleerCreation player realizing");
    result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
    LOGI("pleerCreation finished");
}

}

