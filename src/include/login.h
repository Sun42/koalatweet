#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui/QDialog>
#include "ui_login.h"

namespace Ui
{
        class LoginWidget;
}

class LoginWidget : public QDialog, public Ui_Dialog
{
    Q_OBJECT
public:
        LoginWidget(QWidget *parent = 0);
        ~LoginWidget();

 private slots:
void validated();


private:
    Ui::LoginWidget *   ui;
 };

#endif // LOGIN_H
