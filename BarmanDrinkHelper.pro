QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drinkinfo.cpp \
    login.cpp \
    main.cpp \
    barman.cpp


HEADERS += \
    barman.h \
    drinkinfo.h \
    json.hpp \
    login.h


FORMS += \
    barman.ui \
    drinkinfo.ui \
    login.ui \


INCLUDEPATH += /usr/local/cellar/curl/7.72.0/include
INCLUDEPATH += /usr/local/Cellar/mongo-cxx-driver/3.6.0/include

LIBS += \
    -lcurl
    -ljson

LIBS += \
     -L/usr/local/lib \
     -lmongocxx \
     -lbsoncxx


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
