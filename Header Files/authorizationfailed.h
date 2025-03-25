#ifndef AUTHORIZATIONFAILED_H
#define AUTHORIZATIONFAILED_H

#include <QDialog>

namespace Ui {
class AuthorizationFailed;
}

class AuthorizationFailed : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationFailed(QWidget *parent = nullptr);
    ~AuthorizationFailed();

private:
    Ui::AuthorizationFailed *ui;
};

#endif // AUTHORIZATIONFAILED_H
