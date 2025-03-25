#include "authorizationfailed.h"
#include "ui_authorizationfailed.h"

AuthorizationFailed::AuthorizationFailed(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthorizationFailed)
{
    ui->setupUi(this);
}

AuthorizationFailed::~AuthorizationFailed()
{
    delete ui;
}
