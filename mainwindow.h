#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "anotherwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase dataBase;
    QSqlQuery *query;
    AnotherWindow *signIn = nullptr;
    void cleanupSignIn();
};
#endif // MAINWINDOW_H
