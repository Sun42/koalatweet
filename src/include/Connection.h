#ifndef CONNECTION_H_
# define CONNECTION_H_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>


class	Connection
{
 public:
  static Connection*	getInstance(boost::asio::io_service &, std::string &, std::string &);
  static Connection*	getInstance();
  void			writeLoop(std::string mess);
  void			handleWrite(const boost::system::error_code& error, size_t nb_write, std::string * msg);
  void                  readLoop();
  void                  handleRead(const boost::system::error_code& error, size_t number_bytes_read);
  ~Connection();


 private:
  Connection(boost::asio::io_service &, std::string &, std::string &);
  Connection(Connection const &);
  Connection&		operator=(Connection const &);


  static Connection*		_instance;
  boost::asio::ip::tcp::socket	_socket;
  boost::array<char, 4096>	_rcvBuffer;
  std::string			_saveBuffer;
  bool				_isSet;
};

#endif
