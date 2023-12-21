QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    course.cpp \
    coursedatabase.cpp \
    coursetime.cpp \
    dbhandler.cpp \
    dinic.cpp \
    ek.cpp \
    fenwick_tree.cpp \
    main.cpp \
    mainwindow.cpp \
    multicoursetime.cpp \
    segmenttree.cpp \
    sov1_topsort.cpp \
    teachercourse.cpp \
    topsort.cpp \
    trie.cpp

HEADERS += \
    AlgorithmException.h \
    CourseSystem.h \
    classinfo.h \
    course.h \
    coursedatabase.h \
    coursetime.h \
    dbexceptions.h \
    dbhandler.h \
    dinic.h \
    ek.h \
    fenwick_tree.h \
    mainwindow.h \
    multicoursetime.h \
    segmenttree.h \
    stdAddition.h \
    teachercourse.h \
    topsort.h \
    trie.h

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

DISTFILES += \
    icon/hide.png \
    icon/icon.jpg \
    icon/quit.png

RESOURCES += \
    icon.qrc
