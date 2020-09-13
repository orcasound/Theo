#include "theo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Theo w;
    w.show();

    return a.exec();
}
