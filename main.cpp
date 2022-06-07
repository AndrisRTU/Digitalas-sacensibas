#include <QApplication>
#include "GameHandler.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::unique_ptr<GameHandler> gameHandler  = std::make_unique<GameHandler>();

    return a.exec();
}
