#-------------------------------------------------
#
# Project created by QtCreator 2017-09-30T13:22:39
#
#-------------------------------------------------

QT      += core gui
QT	+= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Panel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

win32 {
	DEFINES += WIN32
	LIBS += -lws2_32
}

linux {
	DEFINES += POSIX
        DEFINES += LINUX
}

macx {
	DEFINES += POSIX
        DEFINES += LINUX
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -fno-strict-aliasing

SOURCES += \
        main.cpp \
        panel.cpp \
	translation.cpp \
	controller.cpp \
	client.cpp \
	login_dialog.cpp \
	protocol/Message.cpp \
	connection.cpp \
	test.cpp \
	configdialog.cpp

HEADERS += \
	panel.h \
	translation.h \
	controller.h \
	login_dialog.h \
	client.h \
	protocol/Message.h \
	signmodel.h \
	connection.h \
	configdialog.h

FORMS += \
        panel.ui

RESOURCES += \
    translations.qrc \
    ssl.qrc
