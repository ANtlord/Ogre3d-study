LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    LOCAL_MODULE    := ForumOgreProject

    LOCAL_LDLIBS	:= -landroid -lc -lm -ldl -llog -lEGL -lGLESv2
    LOCAL_LDLIBS	+= -L/home/nvpopov/apps/ogre1_9/android_build/lib \
		-L/home/nvpopov/apps/ogre1_9/AndroidDependencies/lib/armeabi

    LOCAL_LDLIBS	+= -lPlugin_ParticleFXStatic -lPlugin_OctreeSceneManagerStatic -lRenderSystem_GLES2Static -lOgreRTShaderSystemStatic -lOgreOverlayStatic -lOgreTerrainStatic -lOgrePagingStatic -lOgreVolumeStatic -lOgreMainStatic
    LOCAL_LDLIBS	+= -lzzip -lz -lFreeImage -lfreetype -lOIS \
					   /home/nvpopov/apps/ogre1_9/android_build/systemlibs/armeabi/libsupc++.a \
					   /home/nvpopov/apps/ogre1_9/android_build/systemlibs/armeabi/libstdc++.a \
					   /home/nvpopov/apps/ogre1_9/android_build/SampleBrowserNDK/obj/local/armeabi/libcpufeatures.a
    LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures

	LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 \
		-I/home/nvpopov/apps/empty_ogre_project/include \
		-I/home/nvpopov/apps/ogre1_9/android_build/include \
		-I/home/nvpopov/apps/ogre1_9/OgreMain/include \
		-I/home/nvpopov/apps/ogre1_9/RenderSystems/GLES2/include \
		-I/home/nvpopov/apps/ogre1_9/RenderSystems/GLES2/include/EGL

	LOCAL_CFLAGS += -I/home/nvpopov/apps/android-deps/android-ndk-r9c/sources/cpufeatures \
		-I/home/nvpopov/apps/ogre1_9/Components/RTShaderSystem/include \
		-I/home/nvpopov/apps/ogre1_9/Components/MeshLodGenerator/include \
		-I/home/nvpopov/apps/ogre1_9/Components/Overlay/include \
		-I/home/nvpopov/apps/ogre1_9/Components/Volume/include \
		-I/home/nvpopov/apps/ogre1_9/Components/Terrain/include \
		-I/home/nvpopov/apps/ogre1_9/Components/Paging/include

	LOCAL_CFLAGS += -I/home/nvpopov/apps/ogre1_9/PlugIns/ParticleFX/include \
		-I/home/nvpopov/apps/ogre1_9/PlugIns/OctreeSceneManager/include

	LOCAL_CFLAGS += -I/home/nvpopov/apps/ogre1_9/AndroidDependencies/include \
		-I/home/nvpopov/apps/ogre1_9/AndroidDependencies/include/OIS \
		-I/home/nvpopov/apps/ogre1_9/android_build/Samples/include   

	LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H -DINCLUDE_RTSHADER_SYSTEM=1

        LOCAL_PATH := /home/nvpopov/apps/empty_ogre_project
        LOCAL_SRC_FILES :=  src/main.cpp src/ShaderGeneratorTechniqueResolverListener.cpp 

    include $(BUILD_SHARED_LIBRARY)

    $(call import-module,android/cpufeatures)
    $(call import-module,android/native_app_glue)
