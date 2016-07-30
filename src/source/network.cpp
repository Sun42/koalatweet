#include <iostream>
#include <QObject>
#include <QByteArray>
#include <qdatastream.h>
#include <QChar>

#include "network.h"
#include "mainwindow.h"

QtConnection::QtConnection(QObject* parent)
{
  this->_server = new QTcpSocket(parent);
  MainWindow*	p = MainWindow::getInstance();
  QTcpSocket::connect(this->_server, SIGNAL(stateChanged(QAbstractSocket::SocketState)), p, SLOT(connected(QAbstractSocket::SocketState)));
  QObject::connect(this->_server, SIGNAL(disconnected()), p,  SLOT(leave()));
  QObject::connect(this->_server, SIGNAL(readyRead()), p, SLOT(dataReceived()));
  QObject::connect(this->_server, SIGNAL(connected()), p, SLOT(connect()));
  QTcpSocket::connect(this->_server, SIGNAL(error(QAbstractSocket::SocketError)), p, SLOT(socketError(QAbstractSocket::SocketError)));
}

QtConnection::~QtConnection()
{}

QtConnection::QtConnection(QtConnection const & rhs): _server(rhs._server)
{
}

QtConnection&	QtConnection::operator=(QtConnection const & rhs)
{
  if (this != &rhs)
      this->_server = rhs._server;
  return (*this);
}

void		QtConnection::connection()
{
    std::cout << "je me connect" << std::endl;
    this->_server->abort();
    this->_server->connectToHost("http://twitter.com/", 80);// 10.249.10.2
}

void            QtConnection::proxyConnect(QString host, quint16 port, QString , QString )
{
    this->_server->abort();
    this->_server->connectToHost(host, port);// 10.249.10.2
}

void		QtConnection::disconnect()
{
  std::cout << "Je suis deconecte" << std::endl;
  this->_server->close();
  this->_server->abort();
}

QString const &	QtConnection::getErrorInfo()
{
  std::cout << "je suis la " << std::endl;

  QString	*error = new QString(this->_server->errorString());
  std::cout << "je resuisla : "<< error->toStdString() << std::endl;
  return (*error);
}

void	QtConnection::sendData(unsigned char, QString const & data)
{
  std::string	sendedData;

 // std::cout << "jenvoi kkchose : ->" << code << " " << data.toStdString() << std::endl;
//  sendedData.push_back(code);
  sendedData +=  " " + data.toStdString() + "\n";
  this->_server->write(sendedData.c_str()); // On envoie le paquet
}

int	QtConnection::readData(QString & buffer)
{
  char	dat[4096];
  int	nb_read;

  nb_read = this->_server->read(dat, 4095);
  dat[nb_read] = '\0';
  std::cout << "buffer recu  -->";
  for (int i = 0; i < nb_read; i++)
    {
      std::cout << "[" << dat[i] << "]";
    }
  std::cout << "<---\n";
  buffer.append(dat);
  return (nb_read);
}

void	QtConnection::connect()
{
  std::cout << "you are connected" << std::endl;
}

void	QtConnection::leave()
{
  std::cout << "you are disconnected" << std::endl;
}
/*
void	QtConnection::socketError()
{
  std::cout << "ERROR : " << this->_server->errorString().toStdString() << std::endl;
}
*/
