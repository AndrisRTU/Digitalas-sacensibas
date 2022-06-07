#ifndef CHATLINEEDIT_H
#define CHATLINEEDIT_H
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include "IOnlineEventReceiver.h"

class ChatLineEdit : public QLineEdit {
private:
    QTextEdit& receiver;
    IOnlineEventReceiver* onlineReceiver;
    virtual void keyPressEvent(QKeyEvent* event) override;
    uint64_t lastMesageTime;
    QString initialText;
public:
    ChatLineEdit(QTextEdit& receiver);
    void setInitialText(const QString& text);
    void setOnlineReceiver(IOnlineEventReceiver* receiver);
};

#endif // CHATLINEEDIT_H
