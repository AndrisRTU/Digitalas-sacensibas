#ifndef GAMESTRUCTURES_H
#define GAMESTRUCTURES_H
#include <QMetaType>

enum class Player {
    Player,
    AI
};

Q_DECLARE_METATYPE(Player)

enum class GameTurn {
    FirstPlayer,
    SecondPlayer
};

enum class NewGameState {
    Random,
    FirstPlayerTurn,
    SecondPlayerTurn
};

Q_DECLARE_METATYPE(NewGameState)

enum class Movement {
    Horizontal,
    Vertical
};

#endif // GAMESTRUCTURES_H
