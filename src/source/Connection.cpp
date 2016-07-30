#include "Connection.h"
#include "mainwindow.h"

/************************************/
Connection* Connection::_instance = 0;
/************************************/


Connection*	Connection::getInstance(boost::asio::io_service & serv, std::string & host , std::string& port)
{
  if (!_instance)
    {
      _instance = new Connection(serv, host, port);
    }
  return (_instance);
}

Connection*	Connection::getInstance()
{
  return (_instance);
}


Connection::Connection(boost::asio::io_service & serv, std::string & host , std::string& port) :
  _socket(serv), _isSet(false)
{
  boost::asio::ip::tcp::endpoint	servPoint(boost::asio::ip::address::from_string(host), atoi(port.c_str()));
  std::cout << host << " -- " << port << std::endl;
  this->_socket.connect(servPoint);

  MainWindow::getInstance()->setAuth();
  MainWindow::getInstance()->setLogs();


  this->writeLoop("aa");
  this->readLoop();

}


Connection::~Connection()
{
  std::cerr << "DTOR" << std::endl;
}

void            Connection::readLoop()
{
  std::cout << "Connection::readLoop\n";
  boost::asio::async_read(this->_socket, boost::asio::buffer(this->_rcvBuffer),
                          boost::asio::transfer_at_least(1),
                          boost::bind(&Connection::handleRead, this, //shared_from_this(),
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
  std::cout << "apres\n";
}


void            Connection::handleRead(const boost::system::error_code& error, size_t nb_read)
{
  std::cout << "Connection::handleRead\n";
  if (!error)
    {
      std::cout << "\nBuffer en memoire avant -->" << this->_saveBuffer << "<--->" << std::endl;
      std::cout << "Buffer Recu -->" ;
      for (unsigned int i = 0; i < nb_read; ++i)
        {
          std::cout << "[" << (int)_rcvBuffer[i] << "]";
          this->_saveBuffer.push_back(this->_rcvBuffer[i]);
          this->_rcvBuffer[i] = 0;
        }
      std::cout <<std::endl << this->_saveBuffer;
      this->readLoop();
    }
  else
    {
      std::cout << "erreur";
    }
}

void            Connection::writeLoop(std::string  msg)
{
  std::cout << "Connection::writeLoop" << msg << std::endl;
  std::string   *mess = new std::string(msg);

  std::cout << "avant write\n";
  boost::asio::async_write(this->_socket, boost::asio::buffer(*mess),
                           boost::bind(&Connection::handleWrite, this,
                                       boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, mess)
                           );
  std::cout << "apres write\n";
}

void            Connection::handleWrite(const boost::system::error_code& error, size_t nb_write, std::string * msg)
{
  std::cout << "Connection::handleWrite --->";
  std::cout << std::boolalpha << this->_isSet << "<---" << std::endl;
  if (this->_isSet == false)
    {
      std::cerr << "je lance la boucle ioservice run\n";
      boost::asio::io_service serv;
      this->_isSet = true;
      serv.run();
    }
  std::cout << "Connection::handleWrite\n";
  if (!error)
    {
      if (nb_write < msg->size())
	{
	  std::cout << "je suis ds le if ici\n";
	  this->writeLoop(msg->erase(0, nb_write));
	}
    }
  else
    std::cout << error.message() ;
}
