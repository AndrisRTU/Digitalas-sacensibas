#ifndef BOARDCELL_H
#define BOARDCELL_H
#include "NumberCell.h"
#include <QPushButton>
#include "IBoard.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "GameEnums.h"
#include "IGameConditionMembers.h"

class BoardCell : public QPushButton {
    Q_OBJECT
private:
    const IGameConditionMembers& gameCondition;
    std::unique_ptr<QPropertyAnimation> fadeAnimation;
    std::unique_ptr<QGraphicsOpacityEffect> opacity;
public:
    const NumberCell& cell;
    BoardCell(const NumberCell& cell, const IGameConditionMembers& gameCondition);
    void awake();
    void diactivate();
    void update();
};

#endif // BOARDCELL_H
