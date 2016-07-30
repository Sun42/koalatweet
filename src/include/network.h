#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>
#include <QNetworkProxy>

class	QtConnection
{
 public:
  QtConnection(QObject * parent = 0);
  ~QtConnection();
  QtConnection(QtConnection const & rhs);
  QtConnection&	operator=(QtConnection const & rhs);
  void                  connection();
  void                  sendData(unsigned char code, QString const & data);
  int                   readData(QString & buffer);
  QString const &       getErrorInfo();
  void			disconnect();
  void                  proxyConnect(QString link, quint16 port, QString name, QString pass);

  private slots:
  void			dataReceived();
  void			connect();
  void			leave();
  void                  socketError(QAbstractSocket::SocketError const & error);

 private:
  QTcpSocket*		_server;
  QNetworkProxy*         _proxy;
};

#endif // NETWORK_H
