#ifndef __EXCEPTIONTWEET_H__
# define __EXCEPTIONTWEET_H__

#include <exception>

class	ExceptionTweet : public std::exception
{
 public:
  ExceptionTweet(char const *) throw();
  ExceptionTweet(ExceptionTweet const &) throw();
  ExceptionTweet &	operator=(ExceptionTweet const &) throw();
  ~ExceptionTweet() throw();

  char const *    what() const throw();

 private:
  char const *  _message;
};

#endif /* !__EXCEPTIONTWEET_H__ */
