QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# SOURCES += \
#     main.cpp \
#     mainwindow.cpp

# HEADERS += \
#     mainwindow.h

# FORMS += \
#     mainwindow.ui


HEADERS += include/mainwindow.h \
           include/adjacency_matrix.h \
           include/game_state.h \
           include/map.h \
           include/player_data.h \
           include/singly_linked_list.h \
           include/tank.h \
           include/bullet.h

SOURCES += src/main.cpp \
           src/player_data.cpp \
           src/game_state.cpp \
           src/mainwindow.cpp \
           src/map.cpp \
           src/tank.cpp \
           src/bullet.cpp

FORMS += ui/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
