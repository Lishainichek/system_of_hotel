#include <QApplication>
#include <QPushButton>
#include "host.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    host host;
    return QApplication::exec();
}
