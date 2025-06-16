#include "anotherwindow.h"
#include "mainwindow.h"
#include "ui_anotherwindow.h"

AnotherWindow::AnotherWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AnotherWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/d66739fb-8e53-4420-a742-7417652b0c2e.ico"));
    this->setWindowTitle("SIGN IN");
    QPixmap pix(":/rec/images/exit.png");
    ui->image->setPixmap(pix.scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("path_to_your_database/name_of_your_database.db");
    dataBase.open();
    query = new QSqlQuery(dataBase);
    query->exec("CREATE TABLE IF NOT EXISTS User(Login TEXT PRIMARY KEY, Password TEXT)");
}

AnotherWindow::~AnotherWindow()
{
    cleanupSignUp();
    delete ui;
}

void AnotherWindow::on_pushButton_2_clicked()
{
    if(!signUp){
        signUp = new MainWindow();
        signUp->setFixedSize(signUp->size());
        connect(signUp, &MainWindow::destroyed, this, [this]() {
            signUp = nullptr;
        });
    }
    signUp->show();
    this->close();
}

void AnotherWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    if (login == "") {
        ui->label_3->setText("<i><font size=2 color='red'>Enter login!</font></i>");
        return;
    }
    if (password == "") {
        ui->label_3->setText("<i><font size=2 color='red'>Enter password!</font></i>");
        return;
    }
    query->prepare("SELECT Password FROM User WHERE Login = :login");
    query->bindValue(":login", login);
    query->exec();
    if (query->next()) {
        QString dataBasePassword = query->value(0).toString();
        if (dataBasePassword == password) {
            ui->label_3->setText("<i><font size=2 color='green'>You have successfully signed in!</font></i>");
        } else {
            ui->label_3->setText("<i><font size=2 color='red'>Wrong password!</font></i>");
        }
    } else {
        ui->label_3->setText("<i><font size=2 color='red'>User not found!</font></i>");
    }
}

void AnotherWindow::cleanupSignUp(){
    if(signUp){
        signUp->disconnect();
        signUp->deleteLater();
        signUp = nullptr;
    }
}
