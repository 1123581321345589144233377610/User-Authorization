#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/images/free-icon-authorization-12050714.png");
    int width = pix.width();
    int height = pix.height();
    ui->image->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./users.db");
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
        ui->label_3->setText("<font color='red'>Enter login!</font>");
        return;
    }
    if(password == ""){
        ui->label_3->setText("<font color='red'>Enter password!</font>");
        return;
    }
    query->prepare("SELECT EXISTS(SELECT 1 FROM User WHERE Login = :login);");
    query->bindValue(":login", login);
    query->exec();
    query->next();
    bool exists = query->value(0).toBool();
    if(exists){
        ui->label_3->setText("<font color='red'>User already exist!</font>");
    }else{
        query->prepare("INSERT INTO User (Login, Password) VALUES (:login, :password);");
        query->bindValue(":login", login);
        query->bindValue(":password", password);
        query->exec();
        ui->label_3->setText("<font color='green'>Authorization succesful complete!</font>");
    }
}
