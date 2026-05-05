TEMPLATE = app
CONFIG += console c++17
 CONFIG -= app_bundle
 CONFIG -= qt
#QT += network

INCLUDEPATH += "/home/pi/asio-1.30.2/include" \
                "/home/pi/rapidjson-master/include/rapidjson" \
                "usr/include" \


SOURCES += \
        auditory_stimulus.cpp \
        auditorycontroller.cpp \
        experiment.cpp \
        gc.cpp \
        interfaceconnector.cpp \
        main.cpp \
        pixel.cpp \
        responsecontroller.cpp \
        trial.cpp \
        visual_stimulus.cpp


LIBS += -llgpio -lncurses
LIBS += -levdev

HEADERS += \
    auditory_stimulus.h \
    auditorycontroller.h \
    experiment.h \
    gc.h \
    interfaceconnector.h \
    pixel.h \
    responsecontroller.h \
    trial.h \
    visual_stimulus.h

DISTFILES += \
    config.json \
    sample_experiment.json
