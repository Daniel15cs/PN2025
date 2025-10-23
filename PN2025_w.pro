QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CMAKE_BUILD_TYPE=Debug
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbviewer.cpp \
    formauth.cpp \
    main.cpp \
    mainwindow.cpp \
    stackedwidget.cpp

HEADERS += \
    dbviewer.h \
    formauth.h \
    mainwindow.h \
    stackedwidget.h

FORMS += \
    dbviewer.ui \
    formauth.ui \
    mainwindow.ui \
    stackedwidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
