QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "C:\Users\nicco\Desktop\MultisensorySetup\asio-1.30.2/include" \
                "C:\Users\nicco\Desktop\MultisensorySetup\rapidjson-master/include/rapidjson"



LIBS += -lws2_32

SOURCES += \
    ExperimentStub.cpp \
    addadialog.cpp \
    addvdialog.cpp \
    auditorystimulusstub.cpp \
    edittrialdialog.cpp \
    gc.cpp \
    main.cpp \
    mainwindow.cpp \
    trialstub.cpp \
    visualstimulusstub.cpp

HEADERS += \
    ExperimentStub.h \
    addadialog.h \
    addvdialog.h \
    auditorystimulusstub.h \
    edittrialdialog.h \
    gc.h \
    mainwindow.h \
    trialstub.h \
    visualstimulusstub.h

FORMS += \
    addadialog.ui \
    addvdialog.ui \
    edittrialdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    PsychophysicalInterface_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
