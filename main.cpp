#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CatUI window;
    window.show();

    return app.exec();
}
