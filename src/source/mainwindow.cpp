#include <QWebView>
#include <QNetworkProxy>
#include <QByteArray>
#include <QTextTable>
#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Connection.h"

MainWindow* MainWindow::_uniqueInstance = 0;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow), _loginDial(0),  _apiTwitter(0)
{
  ui->setupUi(this);
  this->restoreMenu();
  QObject::connect(this->ui->btGoToMenuMe, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->actionLogin, SIGNAL(activated()), this, SLOT(loginWindow()));
  QObject::connect(this->ui->btMe, SIGNAL(clicked()), this, SLOT(meClicked()));
  QObject::connect(this->ui->text_but, SIGNAL(clicked()), this, SLOT(sendButProv()));
  QObject::connect(this->ui->btFavorites, SIGNAL(clicked()), this, SLOT(favoritesClicked()));
  QObject::connect(this->ui->btFollowing, SIGNAL(clicked()), this, SLOT(followingClicked()));
  QObject::connect(this->ui->btFollowers, SIGNAL(clicked()), this, SLOT(followersClicked()));
  QObject::connect(this->ui->btPublic, SIGNAL(clicked()), this, SLOT(publicClicked()));
  QObject::connect(this->ui->btSearches, SIGNAL(clicked()), this, SLOT(searchesClicked()));
  QObject::connect(this->ui->btGoToMenuMe, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btGoToMenuFavorites, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btGoToMenuFollowing, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btGoToMenuFollowers, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btGoToMenuPublic, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btGoToMenuSearches, SIGNAL(clicked()), this, SLOT(restoreMenu()));
  QObject::connect(this->ui->btAddItem, SIGNAL(clicked()), this, SLOT(addItem()));
  this->ui->lineEditProxyAddress->setText("10.42.42.61");
  this->ui->lineEditProxyPort->setText("3128");
  this->ui->lineEditProxyUserName->setText("renaut_y");
  this->ui->lineEditProxyPassword->setText("anwEI6[+");
  this->_isConnect = false;
}

void	MainWindow::sendButProv()
{
  ApiTwitter::getInstance()->execCmd(1, "");
}

void    MainWindow::loginWindow()
{
    if (this->_loginDial == 0)
        this->_loginDial = new LoginWidget();
    if (this->_loginDial->exec() == QDialog::Accepted)
    {
        this->connection();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::destroyInstance()
  {
    if (MainWindow::_uniqueInstance != 0)
      {
        delete MainWindow::_uniqueInstance;
        MainWindow::_uniqueInstance = 0;
      }
  }


MainWindow* MainWindow::getInstance()
      {
        if (MainWindow::_uniqueInstance == 0)
          {
            MainWindow::_uniqueInstance = new MainWindow();
          }
        return (MainWindow::_uniqueInstance);
      }

void MainWindow::meClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetMe->setEnabled(true);
  this->ui->btGoToMenuMe->setEnabled(true);
  this->ui->widgetMe->show();
}

void MainWindow::favoritesClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetFavorites->setEnabled(true);
  this->ui->btGoToMenuFavorites->setEnabled(true);
  this->ui->widgetFavorites->show();
}
void MainWindow::followingClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetFollowing->setEnabled(true);
  this->ui->btGoToMenuFollowing->setEnabled(true);
  this->ui->widgetFollowing->show();
}
void MainWindow::followersClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetFollowers->setEnabled(true);
  this->ui->btGoToMenuFollowers->setEnabled(true);
  this->ui->widgetFollowers->show();

}
void MainWindow::publicClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetPublic->setEnabled(true);
  this->ui->btGoToMenuPublic->setEnabled(true);
  this->ui->widgetPublic->show();
}

void MainWindow::searchesClicked()
{
  this->ui->widgetMenu->hide();
  this->ui->widgetSearches->setEnabled(true);
  this->ui->btGoToMenuSearches->setEnabled(true);
  this->ui->widgetSearches->show();

}

void MainWindow::restoreMenu()
{
  this->ui->widgetFavorites->hide();
  this->ui->widgetFollowers->hide();
  this->ui->widgetFollowing->hide();
  this->ui->widgetMe->hide();
  this->ui->widgetPublic->hide();
  this->ui->widgetSearches->hide();
  this->ui->widgetMenu->show();
}

void MainWindow::logOutMode()
{
  this->ui->tabHome->setEnabled(false);
  this->ui->tabProfile->setEnabled(false);
}

// void	MainWindow::dataReceived()
// {
//   int			index;
//   QString		endchar("\n");
//   int			nb_read;

//   nb_read = this->_connection->readData(this->_buffer);
//   std::cout << "\nnb Read : " << nb_read << std::endl;
//   std::cout << "data received -->" << this->_buffer.toStdString() << "<--" << std::endl;
//   while ((index = this->_buffer.indexOf(endchar)) != -1)
//     {
//       std::cout << "jai un antislash N " << std::endl;
//       QString cmd(this->_buffer.toStdString().substr(0, index).c_str());
//       this->setLogInfo("R : " + cmd);
//       this->_buffer.remove(0, index + 1);
//     }
// }

void MainWindow::logInMode()
{
    this->ui->tabHome->setEnabled(true);
    this->ui->tabProfile->setEnabled(true);
}

/*void	MainWindow::socketError(QAbstractSocket::SocketError const & error)
{
  if (error == QAbstractSocket::RemoteHostClosedError)
    {
      this->disconnect();
    }
 this->setLogInfo("ERROR : " + this->_connection->getErrorInfo());
 }*/

void    MainWindow::setAuth() const
{
    QString temp;

    temp = this->ui->lineEditProxyUserName->text();
    temp += ":" + this->ui->lineEditProxyPassword->text();
    QByteArray  bytetemp(temp.toStdString().c_str());
    ApiTwitter::getInstance()->setAuth(bytetemp.toBase64());
}

void    MainWindow::setLogs() const
{
    QString temp;

    temp = this->_login;
    temp += ":" + this->_pass;
    QByteArray  bytetemp(temp.toStdString().c_str());
    ApiTwitter::getInstance()->setLogs(bytetemp.toBase64());
}

void    MainWindow::setLogInfo(QString const & info)
{
  QTextCursor cursor(this->ui->textBrowser->textCursor());
  cursor.movePosition(QTextCursor::End);
  QTextTableFormat tableFormat;
  tableFormat.setBorder(0);
  QTextTable *table = cursor.insertTable(1, 2, tableFormat);
  table->cellAt(0, 0).firstCursorPosition().insertText("< Logs > ");
  table->cellAt(0, 1).firstCursorPosition().insertText(info);
  QScrollBar *bar = this->ui->textBrowser->verticalScrollBar();
  bar->setValue(bar->maximum());
}
/*
void	MainWindow::connected(QAbstractSocket::SocketState const & socketState)
{
  switch (socketState)
  {
      case QAbstractSocket::ConnectedState :
        this->setLogInfo("jai accept()");
        this->setAuth();
        this->setLogs();
        ApiTwitter::getInstance()->execCmd(1, "");
        break;
      case QAbstractSocket::HostLookupState :
        this->setLogInfo("je suis HostLookupState");
        break;
      case QAbstractSocket::UnconnectedState :
        //this->setLogInfo("je suis UnconnectedState");
        break;
      case QAbstractSocket::ConnectingState :
        //this->setLogInfo("je suis ConnectingState");
        //this->setLogInfo("Proxy Is Asked");
        //this->_connection->proxyConnect("proxy.epita.fr", 3128, "sundas_c", "ckstAC<(");
        break;
      case QAbstractSocket::BoundState :
        this->setLogInfo("je suis BoundState");
        break;
      case QAbstractSocket::ClosingState :
        this->setLogInfo("je suis ClosingState");
        break;
      case QAbstractSocket::ListeningState :
        this->setLogInfo("je suis ListeningState");
        break;
      default:
        QString p(socketState + 48);
        this->setLogInfo("je suis default : " + p);
  }
}

void	MainWindow::connect()
{
  std::cout << "you are connected" << std::endl;
}

void	MainWindow::sendData()
{
  this->_connection->sendData(33, this->ui->text_but->text());
  this->ui->text_but->setText("");
}
*/
bool MainWindow::checkProxy() const
{
    return (this->ui->checkProxy->isChecked());
}

void MainWindow::addItem()
{
      QIcon myicon("../img/followers.jpg");
    QListWidgetItem *lst1 =new QListWidgetItem(myicon, "Oaklololololololololololollololololololololololololololo", this->ui->listWidget);
      this->ui->listWidget->insertItem(1,lst1);
    this->ui->listWidget->show();
}

void	MainWindow::connection()
{
  std::string	host;
  std::string	port;

  if (this->ui->checkProxy->isChecked())
    {
      host = this->ui->lineEditProxyAddress->text().toStdString();
      port = this->ui->lineEditProxyPort->text().toStdString();
    }
  else
    {
      host = "http://twitter.com/";
      port = "80";
    }
  boost::asio::io_service serv;
  Connection::getInstance(serv, host, port);
}

/*
void    MainWindow::sendData(QString const & data) const
{
    this->_connection->sendData(3, data);
}
*/
void	MainWindow::leave()
{
  this->setLogInfo("you are disconnected");
}

void    MainWindow::logIn(QString const & userName, QString const & pass)
{
    this->_login = userName;
    this->_pass = pass;
}

