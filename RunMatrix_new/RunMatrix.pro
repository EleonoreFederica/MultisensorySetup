TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
# QT += network

SOURCES += \
        gc.cpp \
        main.cpp \
        matriximage.cpp \
        pixel.cpp

INCLUDEPATH += "/home/pi/rpi-rgb-led-matrix/include" \
            += "/home/pi/rapidjson/include/rapidjson" \
            += "/home/pi/asio-1.30.2/include"

LIBS += -L../../rpi-rgb-led-matrix/lib -l:librgbmatrix.a

HEADERS += \
    gc.h \
    matriximage.h \
    pixel.h

DISTFILES += \
    config.json \
    end_trial_image.json \
    ready_image.json \
    ready_image.json
