#ifndef AUTHORIZATIONCOMPLETE_H
#define AUTHORIZATIONCOMPLETE_H

#include <QDialog>

namespace Ui {
class AuthorizationComplete;
}

class AuthorizationComplete : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationComplete(QWidget *parent = nullptr);
    ~AuthorizationComplete();

private:
    Ui::AuthorizationComplete *ui;
};

#endif // AUTHORIZATIONCOMPLETE_H
