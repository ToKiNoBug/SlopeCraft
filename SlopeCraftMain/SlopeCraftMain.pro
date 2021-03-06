QT       += core gui concurrent network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


TARGET = SlopeCraft

RC_ICONS = others/SlopeCraft.ico

RC_LANG = 0x0004

VERSION += 3.8.1.0

#QMAKE_TARGET_COMPANY = TokiNoBug
#公司名称

QMAKE_TARGET_DESCRIPTION = Map Pixel Art Tool
#描述信息

QMAKE_TARGET_COPYRIGHT = TokiNoBug
#版权信息

QMAKE_TARGET_PRODUCT = SlopeCraft
#产品名称


INCLUDEPATH += D:\CppLibs\eigen-3.4.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    AiCvterParameterDialog.cpp \
    BatchUi.cpp \
    TaskBox.cpp \
    VersionDialog.cpp \
    main.cpp \
    MainWindow.cpp \
    previewwind.cpp \
    tpstrategywind.cpp

HEADERS += \
    AiCvterParameterDialog.h \
    BatchUi.h \
    TaskBox.h \
    VersionDialog.h \
    MainWindow.h \
    previewwind.h \
    tpstrategywind.h

FORMS += \
    others/AiCvterParameterDialog.ui \
    others/BatchUi.ui \
    others/TaskBox.ui \
    others/VersionDialog.ui \
    others/mainwindow.ui \
    others/previewwind.ui \
    others/tpstrategywind.ui

TRANSLATIONS += \
    ./others/SlopeCraft_zh_CN.ts \
    ./others/SlopeCraft_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

RESOURCES += \
    others/BlockTextures.qrc \
    others/Pics.qrc

DISTFILES += \
    others/SlopeCraft.ico


#LIBS += D:\Git\build-SlopeCraft-Desktop_Qt_6_1_0_MinGW_64_bit-Release\SlopeCraftL\release\SlopeCraftL3.dll


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BlockListManager/release/ -lBlockListManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BlockListManager/debug/ -lBlockListManager
else:unix: LIBS += -L$$OUT_PWD/../BlockListManager/ -lBlockListManager

INCLUDEPATH += $$PWD/../BlockListManager
DEPENDPATH += $$PWD/../BlockListManager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BlockListManager/release/libBlockListManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BlockListManager/debug/libBlockListManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BlockListManager/release/BlockListManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BlockListManager/debug/BlockListManager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../BlockListManager/libBlockListManager.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SlopeCraftL/release/ -lSlopeCraftL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SlopeCraftL/debug/ -lSlopeCraftL3
else:unix: LIBS += -L$$OUT_PWD/../SlopeCraftL/ -lSlopeCraftL3

INCLUDEPATH += $$PWD/../SlopeCraftL
DEPENDPATH += $$PWD/../SlopeCraftL


win32: {
    QMAKE_PRE_LINK+= cd /d $${OUT_PWD}/.. &

    CONFIG(release,debug|release): {
        QMAKE_PRE_LINK+=copy /Y .\SlopeCraftL\release\SlopeCraftL3.dll .\SlopeCraftMain\release
    }
    else: {
        QMAKE_PRE_LINK+=copy /Y .\SlopeCraftL\debug\SlopeCraftL3.dll .\SlopeCraftMain\debug
    }
#message($$QMAKE_PRE_LINK)
}
else: {
    message(Copying and pasting SlopeCraftL3.dll on other platforms is not implemented yet. \
        Remind to copy this dynamic linked library manually)
}

