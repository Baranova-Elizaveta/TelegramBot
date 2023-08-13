QT -= gui
QT += network
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        include/networking.cpp \
        include/qttelegrambot.cpp \
        include/types/audio.cpp \
        include/types/callbackquery.cpp \
        include/types/chat.cpp \
        include/types/contact.cpp \
        include/types/document.cpp \
        include/types/location.cpp \
        include/types/message.cpp \
        include/types/photosize.cpp \
        include/types/sticker.cpp \
        include/types/update.cpp \
        include/types/user.cpp \
        include/types/video.cpp \
        include/types/voice.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/networking.h \
    include/qttelegrambot.h \
    include/types/audio.h \
    include/types/callbackquery.h \
    include/types/chat.h \
    include/types/contact.h \
    include/types/document.h \
    include/types/file.h \
    include/types/location.h \
    include/types/message.h \
    include/types/photosize.h \
    include/types/reply/forcereply.h \
    include/types/reply/genericreply.h \
    include/types/reply/inlinekeyboardmarkup.h \
    include/types/reply/replykeyboardhide.h \
    include/types/reply/replykeyboardmarkup.h \
    include/types/reply/replykeyboardremove.h \
    include/types/sticker.h \
    include/types/update.h \
    include/types/user.h \
    include/types/video.h \
    include/types/voice.h
