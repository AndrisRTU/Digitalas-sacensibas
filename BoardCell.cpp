#include "BoardCell.h"

BoardCell::BoardCell(const NumberCell& cell, const IGameConditionMembers& gameCondition) :
    cell(cell),
    gameCondition(gameCondition) {
    QString number = QString::number(cell.getNumber());
    setText(number);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    opacity = std::make_unique<QGraphicsOpacityEffect>();
    opacity->setOpacity(1.0);
    setGraphicsEffect(opacity.get());

    fadeAnimation = std::make_unique<QPropertyAnimation>(opacity.get(), "opacity");
    fadeAnimation->setDuration(500);
    fadeAnimation->setStartValue(1.0);
    fadeAnimation->setEndValue(0.0);
    fadeAnimation->setEasingCurve(QEasingCurve::InCubic);

    QFont font("Arial", 16, QFont::Bold);
    this->setStyleSheet("QPushButton {"
                        "background-color: #A0A0A0;"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "}");
    this->setFont(font);
}

void BoardCell::awake() {
    if (cell.isSelected()) {
        return;
    }
    switch (gameCondition.getTurn()) {
    case GameTurn::FirstPlayer:
        this->setStyleSheet("QPushButton {"
                            "background-color: #3198FF;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: #80C0FF;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "}");
        break;
    case GameTurn::SecondPlayer:
        this->setStyleSheet("QPushButton {"
                            "background-color: #FF9830;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: #FFC480;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "}");
        break;
    }
}

void BoardCell::diactivate() {
    if (cell.isSelected()) {
        return;
    }
    this->setStyleSheet("QPushButton {"
                        "background-color: #A0A0A0;"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "}");
}

void BoardCell::update() {
    fadeAnimation->start();
}
