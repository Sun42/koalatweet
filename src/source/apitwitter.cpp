#include <iostream>
#include <QMapIterator>
#include <QMap>

#include "apitwitter.h"
#include "mainwindow.h"
#include "HttpRequest.h"
#include "Connection.h"

ApiTwitter*	ApiTwitter::_instance = 0;
const QString  ApiTwitter::_host = "http://twitter.com/";

ApiTwitter*	ApiTwitter::getInstance()
{
  if (_instance == 0)
    {
      _instance = new ApiTwitter();
    }
  return (_instance);
}

void	ApiTwitter::destroyInstance()
{
  if (_instance != 0)
    {
      delete _instance;
      _instance = 0;
    }
}

ApiTwitter::ApiTwitter(): _funcCaller()
{
  _funcCaller[1] = &ApiTwitter::auth;
}

ApiTwitter::ApiTwitter(ApiTwitter const &)
{
}

ApiTwitter::~ApiTwitter()
{
}

ApiTwitter &	ApiTwitter::operator=(ApiTwitter const &)
{
  return (*this);
}

void			ApiTwitter::auth(QString& cmd)
{
    if (cmd == "")
    {
        HttpRequest     reqAuth;
        reqAuth.setCommande("GET");
        reqAuth.setRessource(ApiTwitter::_host.toStdString() + "account/verify_credentials.json");
        reqAuth.setHeader("Host", ApiTwitter::_host.toStdString());
        if (MainWindow::getInstance()->checkProxy())
        {
            reqAuth.setHeader("Proxy-Authorization", "Basic " + this->_auth.toStdString());
        }
        reqAuth.setHeader("Authorization", "Basic " + this->_logs.toStdString());
        reqAuth.setHeader("Connection", "close");
	MainWindow::getInstance()->setLogInfo(reqAuth.getFullRequest().c_str());
	Connection::getInstance()->writeLoop(reqAuth.getFullRequest().c_str());
        std::cout << "Voici le sand : -->" << cmd.toStdString() << " <--" << std::endl;
    }
}

void	ApiTwitter::execCmd(int func, QString cmd)
{
  funcPtr f = 0;
  if (this->_funcCaller.contains(func))
    {
      f = this->_funcCaller.value(func);
      (this->*f)(cmd);
    }
  else
    std::cout << "Unknown command has been received : " << cmd.toStdString() << std::endl;
}

void    ApiTwitter::setAuth(QString const & auth)
{
    this->_auth = auth;
}

void    ApiTwitter::setLogs(QString const & logs)
{
    this->_logs = logs;
}
