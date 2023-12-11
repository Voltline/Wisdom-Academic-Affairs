QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coursedatabase.cpp \
    dbhandler.cpp \
    fenwick_tree.cpp \
    main.cpp \
    mainwindow.cpp \
    sov1_topsort.cpp

HEADERS += \
    classinfo.h \
    coursedatabase.h \
    dbexceptions.h \
    dbhandler.h \
    fenwick_tree.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    WAA-Github_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES +=
