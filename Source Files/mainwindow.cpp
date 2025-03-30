#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    this->setWindowIcon(QIcon(":/images/d66739fb-8e53-4420-a742-7417652b0c2e.ico"));
    this->setWindowTitle("SIGN UP");
    QPixmap pix(":/rec/images/add-friend (1).png");
    ui->image->setPixmap(pix.scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("path_to_your_database/name_of_your_database.db");
    dataBase.open();
    query = new QSqlQuery(dataBase);
    query->exec("CREATE TABLE IF NOT EXISTS User(Login TEXT PRIMARY KEY, Password TEXT);");
}

MainWindow::~MainWindow()
{
    cleanupSignIn();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    if(login == ""){
        ui->label_3->setText("<i><font size=2 color='red'>Enter login!</font></i>");
        return;
    }
    if(password == ""){
        ui->label_3->setText("<i><font size=2 color='red'>Enter password!</font></i>");
        return;
    }
    query->prepare("SELECT EXISTS(SELECT 1 FROM User WHERE Login = :login);");
    query->bindValue(":login", login);
    query->exec();
    query->next();
    bool exists = query->value(0).toBool();
    if(exists){
        ui->label_3->setText("<i><font size=2 color='red'>User already exist!</font></i>");
    }else{
        query->prepare("INSERT INTO User (Login, Password) VALUES (:login, :password);");
        query->bindValue(":login", login);
        query->bindValue(":password", password);
        query->exec();
        ui->label_3->setText("<i><font size=2 color='green'>Authorization succesful complete!</font></i>");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!signIn){
        signIn = new AnotherWindow();
        signIn->setFixedSize(signIn->size());
        connect(signIn, &AnotherWindow::destroyed, this, [this]() {
            signIn = nullptr;
        });

    }
    signIn->show();
    this->hide();
}

void MainWindow::cleanupSignIn(){
    if(signIn){
        signIn->disconnect();
        signIn->deleteLater();
        signIn = nullptr;
    }
}
