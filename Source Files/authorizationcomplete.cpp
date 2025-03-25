#include "authorizationcomplete.h"
#include "ui_authorizationcomplete.h"

AuthorizationComplete::AuthorizationComplete(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AuthorizationComplete)
{
    ui->setupUi(this);
}

AuthorizationComplete::~AuthorizationComplete()
{
    delete ui;
}
