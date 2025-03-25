#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("path_to_your_database/your_database_name.db");
    if(dataBase.open()){
        qDebug() << "Open!";
    }else{
        qDebug() << "Not open!";
    }
    query = new QSqlQuery(dataBase);
    query->exec("CREATE TABLE IF NOT EXISTS User(Login TEXT PRIMARY KEY, Password TEXT);");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    if(login == ""){
        QMessageBox::information(this, "Failed!", "Enter login!");
        return;
    }
    if(password == ""){
        QMessageBox::information(this, "Failed!", "Enter password!");
        return;
    }
    query->prepare("SELECT EXISTS(SELECT 1 FROM User WHERE Login = :login);");
    query->bindValue(":login", login);
    query->exec();
    query->next();
    bool exists = query->value(0).toBool();
    if(exists){
        hide();
        failed = new AuthorizationFailed(this);
        failed->show();
    }else{
        query->prepare("INSERT INTO User (Login, Password) VALUES (:login, :password);");
        query->bindValue(":login", login);
        query->bindValue(":password", password);
        query->exec();
        hide();
        success = new AuthorizationComplete(this);
        success->show();
    }
}

