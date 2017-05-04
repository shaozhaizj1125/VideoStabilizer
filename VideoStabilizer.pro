#-------------------------------------------------
#
# Project created by QtCreator 2017-05-02T12:10:33
#
#-------------------------------------------------

QT += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoStabilizer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    INCLUDEPATH += "$$_PRO_FILE_PWD_/OpenCV/Win32/include"
    LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Win32/libs"
    LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Win32/bin/"

    CONFIG(debug, debug|release) {
        LIBS += -lopencv_world310d
    }
    CONFIG(release, debug|release) {
        LIBS += -lopencv_world310
    }
}

android {
    INCLUDEPATH += "$$_PRO_FILE_PWD_/OpenCV/Android/include"

    equals(ANDROID_TARGET_ARCH, armeabi) {
        message(armeabi)
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/libs/armeabi"
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/3rdparty/libs/armeabi"
        ANDROID_EXTRA_LIBS = $$_PRO_FILE_PWD_/OpenCV/Android/libs/armeabi/libopencv_java3.so
    }
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        message(armeabi-v7a)
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/libs/armeabi-v7a"
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/3rdparty/libs/armeabi-v7a"
        ANDROID_EXTRA_LIBS = $$_PRO_FILE_PWD_/OpenCV/Android/libs/armeabi-v7a/libopencv_java3.so
    }
    equals(ANDROID_TARGET_ARCH, arm64-v8a) {
        message(arm64-v8a)
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/libs/arm64-v8a"
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/3rdparty/libs/arm64-v8a"
        ANDROID_EXTRA_LIBS = $$_PRO_FILE_PWD_/OpenCV/Android/libs/arm64-v8a/libopencv_java3.so
    }
    equals(ANDROID_TARGET_ARCH, x86) {
        message(x86)
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/libs/x86"
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/3rdparty/libs/x86"
        ANDROID_EXTRA_LIBS = $$_PRO_FILE_PWD_/OpenCV/Android/libs/x86/libopencv_java3.so
    }
    equals(ANDROID_TARGET_ARCH, x86_64) {
        message(x86_64)
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/libs/x86_64"
        LIBS += -L"$$_PRO_FILE_PWD_/OpenCV/Android/3rdparty/libs/x86_64"
        ANDROID_EXTRA_LIBS = $$_PRO_FILE_PWD_/OpenCV/Android/libs/x86_64/libopencv_java3.so
    }

    LIBS += \
        -lopencv_core       \
        -lopencv_highgui    \
        -lopencv_java3      \
        -lopencv_video      \
        -lopencv_videoio    \
        -lopencv_videostab
}


SOURCES += main.cpp \
        display.cpp \
    video_stabilizer.cpp

HEADERS  += display.h \
    image_converter.h \
    video_stabilizer.h

FORMS    += display.ui


