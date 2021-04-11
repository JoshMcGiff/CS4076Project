QT       += core gui

VERSION = 1.0.0.0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = icon.ico

CONFIG += gnu++17 #Using GNU C++17 standard

CONFIG(debug, debug|release) { #if compiling in debug mode
  DEFINES += ZORK_DEBUG
  CONFIG += console
}

CONFIG(release, debug|release) { #if compiling in release mode
  DEFINES += ZORK_RELEASE
  DEFINES += QT_NO_DEBUG_OUTPUT
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Includes

SOURCES += $$files(Sources/*.cpp)  \

HEADERS += $$files(Includes/*.hpp) \
           $$files(Includes/*.h)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Forms/mainwindow.ui \
    Forms/npcdialogui.ui

RESOURCES += \
    Resources.qrc
