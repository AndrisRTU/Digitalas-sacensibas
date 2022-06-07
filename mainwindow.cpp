#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>

template <typename T>
void addItemIntoCombobox(QComboBox& combobox, const QString& item, T value) {
    combobox.addItem(item, QVariant::fromValue(value));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    handler(nullptr),
    onlineReceiver(nullptr) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->nameLineEdit->setMaxLength(20);

    scoreArea = std::make_unique<GameScoreArea>(*ui->firstPlayerScore, *ui->firstPlayerTextScore, *ui->secondPlayerScore, *ui->secondPlayerTextScore, *ui->winStatisticLabel);

    visualArea = std::make_unique<VisualGameArea>();
    ui->GameActionPage->layout()->addWidget(visualArea.get());

    chatLineEdit = std::make_unique<ChatLineEdit>(*ui->chatTextEdit);
    QGridLayout* layout = reinterpret_cast<QGridLayout*>(ui->LobbyPage->layout());
    layout->addWidget(chatLineEdit.get(), 12, 1, 1, 2);

    addItemIntoCombobox(*ui->firstTurnCombobox, "Random", NewGameState::Random);
    addItemIntoCombobox(*ui->firstTurnCombobox, "First player", NewGameState::FirstPlayerTurn);
    addItemIntoCombobox(*ui->firstTurnCombobox, "Second player", NewGameState::SecondPlayerTurn);

    addItemIntoCombobox(*ui->firstTurnOnlineCombobox, "Random", NewGameState::Random);
    addItemIntoCombobox(*ui->firstTurnOnlineCombobox, "First player", NewGameState::FirstPlayerTurn);
    addItemIntoCombobox(*ui->firstTurnOnlineCombobox, "Second player", NewGameState::SecondPlayerTurn);

    addItemIntoCombobox(*ui->firstPlayerCombobox, "Player", Player::Player);
    addItemIntoCombobox(*ui->firstPlayerCombobox, "AI", Player::AI);

    for (int i = 1; i <= 5; i++) {
        addItemIntoCombobox(*ui->firstPlayerAIDifficultyCombobox, QString::number(i), i);
    }

    addItemIntoCombobox(*ui->secondPlayerCombobox, "Player", Player::Player);
    addItemIntoCombobox(*ui->secondPlayerCombobox, "AI", Player::AI);

    for (int i = 1; i <= 5; i++) {
        addItemIntoCombobox(*ui->secondPlayerAIDifficultyCombobox, QString::number(i), i);
    }

    for (int i = 5; i <= 8; i++) {
        const QString size = QString::number(i);
        addItemIntoCombobox(*ui->boardSizeCombobox, size + "x" + size, i);
        addItemIntoCombobox(*ui->boardSizeOnlineCombobox, size + "x" + size, i);
    }

    for (int i = 15; i <= 60; i += 15) {
        addItemIntoCombobox(*ui->timerOnlineCombobox, QString::number(i), i);
    }

    ui->firstPlayerAIDifficultyCombobox->hide();
    ui->secondPlayerAIDifficultyCombobox->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_PlayLocalGameButton_clicked() {
    goToLocalGame();
}

void MainWindow::on_ReturnToMainMenuButton_clicked() {
    goToMainMenu();
}

void MainWindow::goToMainMenu() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::goToLocalGame() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::goToGameAction() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::goToHostPage() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::goToLobbyPage() {
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::goToGameModePage() {
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::goToCreditsPage() {
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::setSlotsLocalGame() {
    ui->returnButton->disconnect();
    ui->restartButton->disconnect();
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::leaveLocalGame);
    connect(ui->restartButton, &QAbstractButton::clicked, this, &MainWindow::restartLocalGame);
}

void MainWindow::setSlotsOnlineGame() {
    ui->returnButton->disconnect();
    ui->restartButton->disconnect();
    connect(ui->returnButton, &QAbstractButton::clicked, this, &MainWindow::leaveOnlineGame);
    connect(ui->restartButton, &QAbstractButton::clicked, this, &MainWindow::restartOnlineGame);
}

void MainWindow::setComboboxIsAcitve(bool isActive) {
    ui->firstPlayerOnlineCombobox->setEnabled(isActive);
    ui->boardSizeOnlineCombobox->setEnabled(isActive);
    ui->firstTurnOnlineCombobox->setEnabled(isActive);
    ui->timerOnlineCombobox->setEnabled(isActive);
}

void MainWindow::startLocalGame() {
    const NewGameState gameState = qvariant_cast<NewGameState>(ui->firstTurnCombobox->currentData());
    const uint8_t boardSize = qvariant_cast<uint8_t>(ui->boardSizeCombobox->currentData());
    const Player firstPlayer = qvariant_cast<Player>(ui->firstPlayerCombobox->currentData());
    const uint8_t firstPlayerDifficulty = qvariant_cast<uint8_t>(ui->firstPlayerAIDifficultyCombobox->currentText());
    const Player secondPlayer = qvariant_cast<Player>(ui->secondPlayerCombobox->currentData());
    const uint8_t secondPlayerDifficulty = qvariant_cast<uint8_t>(ui->secondPlayerAIDifficultyCombobox->currentText());
    handler->startNewGame(gameState, boardSize, firstPlayer, firstPlayerDifficulty, secondPlayer, secondPlayerDifficulty);
    goToGameAction();
}

void MainWindow::setGameHandler(IGameHandler* handler) {
    this->handler = handler;
}

void MainWindow::setOnlineReceiver(IOnlineEventReceiver* onlineReceiver) {
    this->onlineReceiver = onlineReceiver;
    chatLineEdit->setOnlineReceiver(onlineReceiver);
}

uint8_t MainWindow::getBoardSize() const {
    return qvariant_cast<uint8_t>(ui->boardSizeCombobox->currentData());
}

GameScoreArea& MainWindow::getGameScoreArea() {
    return *scoreArea;
}

VisualGameArea& MainWindow::getVisualGameArea() {
    return *visualArea;
}

void MainWindow::lobbyJoined() {
    ui->chatTextEdit->clear();
    chatLineEdit->clear();
    ui->startGameOnlineButton->hide();
    setComboboxIsAcitve(false);
    goToLobbyPage();
}

void MainWindow::eventHappened(OnlineGameEvent event, const QString &string) {
    switch (event) {
    case OnlineGameEvent::wroteToChat:
        ui->chatTextEdit->append(string);
        break;
    case OnlineGameEvent::firstPlayerBoxChanged:
        ui->firstPlayerOnlineCombobox->setCurrentText(string);
        break;
    case OnlineGameEvent::boardSizeBoxChanged:
        ui->boardSizeOnlineCombobox->setCurrentText(string + "x" + string);
        break;
    case OnlineGameEvent::firstTurnBoxChanged:
        ui->firstTurnOnlineCombobox->setCurrentText(string);
        break;
    case OnlineGameEvent::timerBoxChanged:
        ui->timerOnlineCombobox->setCurrentText(string);
        break;
    }
}

void MainWindow::on_startLocalGame_clicked() {
    setSlotsLocalGame();
    ui->gameActionInformativeLabel->clear();
    ui->restartButton->show();
    startLocalGame();
}

void MainWindow::on_PlayOnlineGameButton_clicked() {
    goToGameModePage();
}

void MainWindow::on_pushButton_clicked() {
    goToMainMenu();
}

void MainWindow::on_firstPlayerCombobox_currentIndexChanged(int index) {
    const Player firstPlayer = qvariant_cast<Player>(ui->firstPlayerCombobox->currentData());
    if (firstPlayer == Player::AI) {
        ui->firstPlayerAIDifficultyCombobox->show();
    }
    else {
        ui->firstPlayerAIDifficultyCombobox->hide();
    }
}

void MainWindow::on_secondPlayerCombobox_currentIndexChanged(int index) {
    const Player firstPlayer = qvariant_cast<Player>(ui->secondPlayerCombobox->currentData());
    if (firstPlayer == Player::AI) {
        ui->secondPlayerAIDifficultyCombobox->show();
    }
    else {
        ui->secondPlayerAIDifficultyCombobox->hide();
    }
}

void MainWindow::on_hostButton_clicked(){
    if (ui->nameLineEdit->text().trimmed().isEmpty()) {
        return;
    }
    if (ui->portLineEdit->text().trimmed().isEmpty()) {
        return;
    }
    chatLineEdit->clear();
    ui->chatTextEdit->clear();
    ui->startGameOnlineButton->show();
    ui->firstPlayerOnlineCombobox->clear();
    setComboboxIsAcitve(true);
    const QString name = ui->nameLineEdit->text();
    handler->hostGame(ui->portLineEdit->text().toInt(), name);
    addPlayersToCombobox(name);
    chatLineEdit->setInitialText(name + ": ");
    goToLobbyPage();
}

void MainWindow::on_joinButton_clicked() {
    if (ui->nameLineEdit->text().trimmed().isEmpty()) {
        return;
    }
    if (ui->IPAddressLineEdit->text().trimmed().isEmpty()) {
        return;
    }
    if (ui->portLineEdit->text().trimmed().isEmpty()) {
        return;
    }
    ui->firstPlayerOnlineCombobox->clear();
    const QString name = ui->nameLineEdit->text();
    addPlayersToCombobox(name);
    chatLineEdit->setInitialText(name + ": ");
    handler->joinGame(ui->IPAddressLineEdit->text(), ui->portLineEdit->text().toUInt(), ui->nameLineEdit->text().trimmed());
}

void MainWindow::on_pushButton_2_clicked() {
    handler->lobbyLeft();
    goToHostPage();
}

NewGameState MainWindow::getFirstPlayerTurn() {
    return qvariant_cast<NewGameState>(ui->firstTurnOnlineCombobox->currentData());
}

QString MainWindow::getFirstPlayer() {
    return ui->firstPlayerOnlineCombobox->currentText();
}

uint8_t MainWindow::getBoardSize() {
    return qvariant_cast<uint8_t>(ui->boardSizeOnlineCombobox->currentData());
}

int MainWindow::getTimer() {
    return qvariant_cast<int>(ui->timerOnlineCombobox->currentData());
}

void MainWindow::addPlayersToCombobox(const QString& str) {
    ui->firstPlayerOnlineCombobox->addItem(str);
}

void MainWindow::removePlayersFromCombobox(const QString& str) {
    ui->firstPlayerOnlineCombobox->removeItem(ui->firstPlayerOnlineCombobox->findText(str));
}

void MainWindow::on_firstPlayerOnlineCombobox_activated(int index) {
    if (!onlineReceiver) {
        return;
    }
    onlineReceiver->receiveEvent(OnlineGameEvent::firstPlayerBoxChanged, getFirstPlayer());
}

void MainWindow::on_boardSizeOnlineCombobox_activated(int index) {
    if (!onlineReceiver) {
        return;
    }
    onlineReceiver->receiveEvent(OnlineGameEvent::boardSizeBoxChanged, QString::number(getBoardSize()));
}

void MainWindow::on_firstTurnOnlineCombobox_activated(int index) {
    if (!onlineReceiver) {
        return;
    }
    QString firstTurn;
    if (getFirstPlayerTurn() == NewGameState::Random) {
        firstTurn = "Random";
    }
    else if (getFirstPlayerTurn() == NewGameState::FirstPlayerTurn) {
        firstTurn = "First player";
    }
    else {
        firstTurn = "Second player";
    }
    onlineReceiver->receiveEvent(OnlineGameEvent::firstTurnBoxChanged, firstTurn);
}

void MainWindow::on_timerOnlineCombobox_activated(int index) {
    if (!onlineReceiver) {
        return;
    }
    onlineReceiver->receiveEvent(OnlineGameEvent::timerBoxChanged, QString::number(getTimer()));
}

void MainWindow::on_startGameOnlineButton_clicked() {
    setSlotsOnlineGame();
    ui->gameActionInformativeLabel->clear();
    ui->restartButton->show();
    handler->startOnlineGame();
    goToGameAction();
}

void MainWindow::restartLocalGame() {
    handler->stopGame();
    startLocalGame();
}

void MainWindow::leaveLocalGame() {
    handler->stopGame();
    goToLocalGame();
}

void MainWindow::restartOnlineGame() {
    handler->startOnlineGame();
}

void MainWindow::leaveOnlineGame() {
    goToLobbyPage();
    onlineReceiver->receiveEvent(OnlineGameEvent::returnedToLobby);
}

void MainWindow::setMessageToInformativeLabel(const QString& str) {
    ui->gameActionInformativeLabel->setText(str);
}

void MainWindow::clientConnected() {
    ui->gameActionInformativeLabel->clear();
    ui->restartButton->hide();
    setSlotsOnlineGame();
    goToGameAction();
}

void MainWindow::on_pushButton_3_clicked() {
    goToMainMenu();
}

void MainWindow::on_PlayHostedGameButton_clicked() {
    goToHostPage();
}

void MainWindow::on_GoToCredits_clicked() {
    goToCreditsPage();
}
