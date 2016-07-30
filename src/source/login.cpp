#include "login.h"
#include "mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QDialog(parent)
{
        this->setupUi(this);
        this->connect(this->validBox, SIGNAL(accepted()), SLOT(validated()));
    this->lineUserName->setText("sundas_c");
    this->linePass->setText("sundas_c");
}

LoginWidget::~LoginWidget()
{

}

void    LoginWidget::validated()
{
    MainWindow::getInstance()->logIn(this->lineUserName->text(), this->linePass->text());
    this->lineUserName->setText("");
    this->linePass->setText("");
}
