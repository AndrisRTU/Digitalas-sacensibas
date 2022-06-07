#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VisualGameArea.h"
#include "GameScoreArea.h"
#include "IGameHandler.h"
#include "ChatLineEdit.h"
#include "IMainWindow.h"
#include "IOnlineEventReceiver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    std::unique_ptr<GameScoreArea> scoreArea;
    std::unique_ptr<VisualGameArea> visualArea;
    std::unique_ptr<ChatLineEdit> chatLineEdit;
    IGameHandler* handler;
    IOnlineEventReceiver* onlineReceiver;
    void goToMainMenu();
    void goToLocalGame();
    virtual void goToGameAction() override;
    void goToHostPage();
    virtual void goToLobbyPage() override;
    void goToGameModePage();
    void goToCreditsPage();
    void setSlotsLocalGame();
    void setSlotsOnlineGame();
    void setComboboxIsAcitve(bool isActive);
private slots:
    void on_PlayLocalGameButton_clicked();
    void on_ReturnToMainMenuButton_clicked();
    void on_startLocalGame_clicked();
    void on_PlayOnlineGameButton_clicked();
    void on_pushButton_clicked();
    void on_firstPlayerCombobox_currentIndexChanged(int index);
    void on_secondPlayerCombobox_currentIndexChanged(int index);
    void on_hostButton_clicked();
    void on_joinButton_clicked();
    void on_pushButton_2_clicked();
    void on_firstPlayerOnlineCombobox_activated(int index);
    void on_boardSizeOnlineCombobox_activated(int index);
    void on_firstTurnOnlineCombobox_activated(int index);
    void on_timerOnlineCombobox_activated(int index);
    void on_startGameOnlineButton_clicked();
    void restartLocalGame();
    void leaveLocalGame();
    void restartOnlineGame();
    void leaveOnlineGame();
    void on_pushButton_3_clicked();

    void on_PlayHostedGameButton_clicked();

    void on_GoToCredits_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startLocalGame();
    void gameEnded();
    void setGameHandler(IGameHandler* handler);
    void setOnlineReceiver(IOnlineEventReceiver* onlineReceiver);
    uint8_t getBoardSize() const;
    GameScoreArea& getGameScoreArea();
    VisualGameArea& getVisualGameArea();
    virtual void lobbyJoined() override;
    virtual void eventHappened(OnlineGameEvent event, const QString& string) override;
    virtual NewGameState getFirstPlayerTurn() override;
    virtual QString getFirstPlayer() override;
    virtual uint8_t getBoardSize() override;
    virtual int getTimer() override;
    virtual void addPlayersToCombobox(const QString& str) override;
    virtual void removePlayersFromCombobox(const QString& str) override;
    virtual void setMessageToInformativeLabel(const QString& str) override;
    virtual void clientConnected() override;
};
#endif // MAINWINDOW_H
