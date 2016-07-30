#include "ExceptionTweet.h"

ExceptionTweet::ExceptionTweet(const char *message)  throw() : _message(message)
{}

ExceptionTweet::~ExceptionTweet() throw()
{}

ExceptionTweet::ExceptionTweet(ExceptionTweet const & obj) throw() : _message(obj._message)
{}

ExceptionTweet &	ExceptionTweet::operator=(ExceptionTweet const & obj) throw()
{
  if (this != &obj)
    {
      this->_message = obj._message;
    }
  return (*this);
}

char const *    ExceptionTweet::what() const throw()
{
  return (this->_message);
}
