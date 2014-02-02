LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    LOCAL_MODULE    := GeomWars

    OGRE_PATH		:= /home/nazak/dev/ogre19-test
    OGRE_ANDROID_PATH := /home/nazak/dev/ogre19-test/android_build

    LOCAL_LDLIBS	:= -landroid -lc -lm -ldl -llog -lEGL -lGLESv2
    LOCAL_LDLIBS	+= -L$(OGRE_ANDROID_PATH)/lib \
		-L$(OGRE_PATH)/AndroidDependencies/lib/armeabi

    LOCAL_LDLIBS	+= -lPlugin_ParticleFXStatic -lPlugin_OctreeSceneManagerStatic -lRenderSystem_GLES2Static -lOgreRTShaderSystemStatic -lOgreOverlayStatic -lOgreTerrainStatic -lOgrePagingStatic -lOgreVolumeStatic -lOgreMainStatic
    LOCAL_LDLIBS	+= -lzzip -lz -lFreeImage -lfreetype -lOIS \
					   $(OGRE_ANDROID_PATH)/systemlibs/armeabi/libsupc++.a \
					   $(OGRE_ANDROID_PATH)/systemlibs/armeabi/libstdc++.a \
					   $(OGRE_ANDROID_PATH)/SampleBrowserNDK/obj/local/armeabi/libcpufeatures.a
    LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures

	LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 \
		-I$(OGRE_ANDROID_PATH)/include \
		-I$(OGRE_PATH)/OgreMain/include \
		-I$(OGRE_PATH)/RenderSystems/GLES2/include \
		-I$(OGRE_PATH)/RenderSystems/GLES2/include/EGL

	LOCAL_CFLAGS += -I/opt/android-ndk/sources/cpufeatures \
		-I$(OGRE_PATH)/Components/RTShaderSystem/include \
		-I$(OGRE_PATH)/Components/Overlay/include \
		-I$(OGRE_PATH)/Components/Volume/include \
		-I$(OGRE_PATH)/Components/Terrain/include \
		-I$(OGRE_PATH)/Components/Paging/include

	LOCAL_CFLAGS += -I$(OGRE_PATH)/PlugIns/ParticleFX/include \
		-I$(OGRE_PATH)/PlugIns/OctreeSceneManager/include

	LOCAL_CFLAGS += -I$(OGRE_PATH)/AndroidDependencies/include \
		-I$(OGRE_PATH)/AndroidDependencies/include/OIS \
		-I$(OGRE_ANDROID_PATH)/Samples/include \
		-I$(LOCAL_PATH)/../   

	LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H -DINCLUDE_RTSHADER_SYSTEM=1

        LOCAL_PATH := ../
        LOCAL_SRC_FILES := gwApp.cpp gwAndroidSys.cpp ShaderGeneratorTechniqueResolverListener.cpp

    include $(BUILD_SHARED_LIBRARY)

    $(call import-module,android/cpufeatures)
    $(call import-module,android/native_app_glue)
