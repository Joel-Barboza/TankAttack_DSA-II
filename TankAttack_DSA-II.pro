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
           include/game_menu_window.h \
           include/data_pair.h \
           include/game_state.h \
           include/how_to_play_window.h \
           include/map.h \
           include/player_data.h \
           include/queue.h \
           include/singly_linked_list.h \
           include/square_items.h \
           include/tank.h \
           include/bullet.h

SOURCES += src/main.cpp \
           src/game_menu_window.cpp \
           src/how_to_play_window.cpp \
           src/player_data.cpp \
           src/game_state.cpp \
           src/mainwindow.cpp \
           src/map.cpp \
           src/square_items.cpp \
           src/tank.cpp \
           src/bullet.cpp


FORMS += ui/mainwindow.ui

RESOURCES += images/red_tank.png \
             images/blue_tank.png \
             images/yellow_tank.png \
             images/lightblue_tank.png



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
