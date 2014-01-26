LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    LOCAL_MODULE    := ForumOgreProject

    LOCAL_LDLIBS	:= -landroid -lc -lm -ldl -llog -lEGL -lGLESv2
    LOCAL_LDLIBS	+= -L/home/uantlord/Develop/ogre/ogre_clean_backup/build_android/lib \
		-L/home/uantlord/Develop/ogre/ogre_clean_backup/AndroidDependencies/lib/armeabi-v7a

    LOCAL_LDLIBS	+= -lPlugin_ParticleFXStatic -lPlugin_OctreeSceneManagerStatic -lRenderSystem_GLES2Static -lOgreRTShaderSystemStatic -lOgreMeshLodGeneratorStatic -lOgreOverlayStatic -lOgreTerrainStatic -lOgrePagingStatic -lOgreVolumeStatic -lOgreMainStatic
    LOCAL_LDLIBS	+= -lzzip -lz -lFreeImage -lfreetype -lOIS \
					   /home/uantlord/Develop/ogre/ogre_clean_backup/build_android/systemlibs/armeabi-v7a/libsupc++.a \
					   /home/uantlord/Develop/ogre/ogre_clean_backup/build_android/systemlibs/armeabi-v7a/libstdc++.a \
					   /home/uantlord/Develop/ogre/ogre_clean_backup/build_android/SampleBrowserNDK/obj/local/armeabi-v7a/libcpufeatures.a
    LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures

	LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/build_android/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/OgreMain/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/RenderSystems/GLES2/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/RenderSystems/GLES2/include/EGL

	LOCAL_CFLAGS += -I/opt/android-ndk/sources/cpufeatures \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/RTShaderSystem/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/MeshLodGenerator/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/Overlay/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/Volume/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/Terrain/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/Components/Paging/include

	LOCAL_CFLAGS += -I/home/uantlord/Develop/ogre/ogre_clean_backup/PlugIns/ParticleFX/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/PlugIns/OctreeSceneManager/include

	LOCAL_CFLAGS += -I/home/uantlord/Develop/ogre/ogre_clean_backup/AndroidDependencies/include \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/AndroidDependencies/include/OIS \
		-I/home/uantlord/Develop/ogre/ogre_clean_backup/build_android/Samples/include   

	LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H -DINCLUDE_RTSHADER_SYSTEM=1

        LOCAL_PATH := /home/uantlord/Develop/ForumOgreProj/
        LOCAL_SRC_FILES := main.cpp

    include $(BUILD_SHARED_LIBRARY)

    $(call import-module,android/cpufeatures)
    $(call import-module,android/native_app_glue)
