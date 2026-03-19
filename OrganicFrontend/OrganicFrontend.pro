QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdminViewWindow.cpp \
    ChartWindow.cpp \
    FirstLoginWindow.cpp \
    MainViewWindow.cpp \
    NewTaskWindow.cpp \
    RegistrationWindow.cpp \
    WelcomeWindow.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AdminViewWindow.h \
    ChartWindow.h \
    DTOdata/Organization.h \
    DTOdata/Task.h \
    DTOdata/UserData.h \
    FirstLoginWindow.h \
    MainViewWindow.h \
    MainWindow.h \
    NewTaskWindow.h \
    Organization.h \
    RegistrationWindow.h \
    Task.h \
    UserData.h \
    WebRequest.h \
    WelcomeWindow.h

FORMS += \
    AdminViewWindow.ui \
    ChartWindow.ui \
    FirstLoginWindow.ui \
    MainViewWindow.ui \
    NewTaskWindow.ui \
    RegistrationWindow.ui \
    WelcomeWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
