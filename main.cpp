#include "src/App.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    // QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    QApplication a(argc, argv);
    App w;
    w.show();
    return a.exec();
}
