#include "mainwindow.h"
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/resources/images/free-icon-login-15867136.ico"));
    w.setFixedSize(w.size());
    w.show();
    return a.exec();
}
