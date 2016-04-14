TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11 opencv

SOURCES += main.cpp \
    MyFilte.cpp \
    MyFilterRunnable.cpp \
    converter.cpp	\
    cvmatandqimage.cpp \
    FrameToImage.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


HEADERS += \
    MyFilter.h \
    MyFilterRunnable.h \
    converter.h \
    cvmatandqimage.h  \
    FrameToImage.h



!android {
    INCLUDEPATH += /usr/local/include/opencv
    LIBS += -L/usr/local/lib \
            -lopencv_core \
            -lopencv_imgcodecs \
            -lopencv_highgui \
            -lopencv_videoio \
#            -lopencv_cudaoptflow \
#            -lopencv_cudaarithm \
            -lopencv_imgproc \
#            -lopencv_cudawarping \
#            -lopencv_cudaimgproc \
#            -lopencv_cudalegacy \
#            -lopencv_cudafilters \
#            -lopencv_cudabgsegm \
#            -lopencv_cudafeatures2d \
            -lopencv_features2d \
            -lopencv_calib3d \
#            -lopencv_cudaobjdetect\
            -lopencv_ml
}


INCLUDEPATH += "/home/Android/OpenCV-android-sdk/sdk/native/jni/include"



android {
    LIBS += \
        -L"/home/Android/OpenCV-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a"\
        -L"/home/Android/OpenCV-android-sdk/sdk/native/libs/armeabi-v7a"\
        -llibtiff\
        -llibjpeg\
        -llibjasper\
        -llibpng\
        -lIlmImf\
        -ltbb\
        -lopencv_core\
#        -lopencv_androidcamera\
#        -lopencv_flann\
        -lopencv_imgproc\
#        -lopencv_highgui\
#        -lopencv_features2d\
#        -lopencv_calib3d\
#        -lopencv_ml\
#        -lopencv_objdetect\
        -lopencv_video\
#        -lopencv_contrib\
        -lopencv_photo\
        -lopencv_java3\
#        -lopencv_legacy\
#        -lopencv_ocl\
#        -lopencv_stitching\
#        -lopencv_superres\
#        -lopencv_ts\
        -lopencv_videostab

 #Enable automatic NEON vectorization
    QMAKE_CXXFLAGS -= -mfpu=vfp
    QMAKE_CXXFLAGS_RELEASE -= -mfpu=vfp
    QMAKE_CXXFLAGS += -mfpu=neon -ftree-vectorize -ftree-vectorizer-verbose=1 -mfloat-abi=softfp
    QMAKE_CXXFLAGS_RELEASE += -mfpu=neon -ftree-vectorize -ftree-vectorizer-verbose=1 -mfloat-abi=softfp

#    ANDROID_PACKAGE_SOURCE_DIR=$$_PRO_FILE_PWD_/android
}


contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../OpenCV-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_java3.so
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
