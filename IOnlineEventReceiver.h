#ifndef IONWINDOWCOMPONENTCHANGERECEIVER_H
#define IONWINDOWCOMPONENTCHANGERECEIVER_H
#include <QString>
#include "OnlineGameEvent.h"

class IOnlineEventReceiver {
public:
    virtual void receiveEvent(OnlineGameEvent event, const QString& item = "") = 0;
};

#endif // IONWINDOWCOMPONENTCHANGERECEIVER_H
