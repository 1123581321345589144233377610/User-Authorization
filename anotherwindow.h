#ifndef ANOTHERWINDOW_H
#define ANOTHERWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class AnotherWindow;
}

class AnotherWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnotherWindow(QWidget *parent = nullptr);
    ~AnotherWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AnotherWindow *ui;
    QSqlDatabase dataBase;
    QSqlQuery *query;
    QMainWindow *signUp = nullptr;
    void cleanupSignUp();
};

#endif // ANOTHERWINDOW_H
