QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    BoardCell.cpp \
    ChatLineEdit.cpp \
    Client.cpp \
    GameCondition.cpp \
    GameController.cpp \
    GameEngine.cpp \
    GameHandler.cpp \
    GameOnlineComponent.cpp \
    GameScene.cpp \
    GameScoreArea.cpp \
    IngameAI.cpp \
    IngamePlayer.cpp \
    MainWindow.cpp \
    Node.cpp \
    NumberCell.cpp \
    PlayerController.cpp \
    RandomGenerator.cpp \
    Server.cpp \
    VisualGameArea.cpp \
    main.cpp

HEADERS += \
    Board.h \
    BoardCell.h \
    ChatLineEdit.h \
    Client.h \
    GameCondition.h \
    GameController.h \
    GameEngine.h \
    GameEnums.h \
    GameHandler.h \
    GameOnlineComponent.h \
    GameScene.h \
    GameScoreArea.h \
    IBoard.h \
    IGameConditionChanger.h \
    IGameConditionMembers.h \
    IGameHandler.h \
    IGameOnlineComponent.h \
    IGamePositionReceiver.h \
    IGameScene.h \
    IGameStatsListener.h \
    IIngameAI.h \
    IIngamePlayer.h \
    IMainWindow.h \
    IOnlineEventReceiver.h \
    IngameAI.h \
    IngamePlayer.h \
    MainWindow.h \
    Node.h \
    NumberCell.h \
    OnlineGameEvent.h \
    PlayerController.h \
    RandomGenerator.h \
    Server.h \
    VisualGameArea.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
