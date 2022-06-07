#include "ChatLineEdit.h"
#include <QDateTime>

ChatLineEdit::ChatLineEdit(QTextEdit& receiver) :
    receiver(receiver),
    lastMesageTime(0),
    initialText("") {
    setMaxLength(200);
}

void ChatLineEdit::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return) {
        uint64_t time = QDateTime::currentSecsSinceEpoch();
        if (time - lastMesageTime < 1) {
            return;
        }
        lastMesageTime = time;
        const QString message = "[" + QDateTime::currentDateTime().time().toString() + QString("] ") + initialText + text();
        receiver.append(message);
        if (onlineReceiver) {
            onlineReceiver->receiveEvent(OnlineGameEvent::wroteToChat, text());
        }
        setText("");
    }
    else {
        QLineEdit::keyPressEvent(event);
    }
}

void ChatLineEdit::setInitialText(const QString& text) {
    this->initialText = text;
}

void ChatLineEdit::setOnlineReceiver(IOnlineEventReceiver* receiver) {
    this->onlineReceiver = receiver;
}
