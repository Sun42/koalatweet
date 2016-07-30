#include "HttpRequest.h"

const std::string	HttpRequest::separator = "\r\n";
const std::string	HttpRequest::httpVersion = "HTTP/1.1";

HttpRequest::HttpRequest()
{
  this->_headers["Content-Length"] = "0";
}

HttpRequest::~HttpRequest()
{
}

HttpRequest::HttpRequest(HttpRequest const &)
{
}

HttpRequest&	HttpRequest::operator=(HttpRequest const &)
{
  return (*this);
}

void		HttpRequest::setCommande(std::string  com)
{
  this->_commande = com;
}

void		HttpRequest::setRessource(std::string  res)
{
  this->_ressource = res;
}

void		HttpRequest::setHeader(std::string  key, std::string  value)
{
  std::map<std::string, std::string>::iterator	it;
  it = this->_headers.find(key);

  if (it != this->_headers.end())
    {
      (*it).second = value;
    }
  else
    {
      this->_headers.insert(std::pair<std::string, std::string>(key, value));
    }
}

void		HttpRequest::setContent(std::string & content)
{
  this->_content = content;
}

std::string	HttpRequest::getCommande() const
{
  std::string	line_com = this->_commande + " " + this->_ressource + " " + HttpRequest::httpVersion;
  return (line_com + HttpRequest::separator);
}

std::string	HttpRequest::getHeaders() const
{
  std::string					headers("");
  std::map<std::string, std::string>::const_iterator	it;

  for (it = this->_headers.begin(); it != this->_headers.end(); ++it)
    {
      headers += (*it).first + ": " + (*it).second + HttpRequest::separator;
    }
  return (headers);
}

std::string	HttpRequest::getFullRequest() const
{
  std::string	fRequest;

  fRequest = this->getCommande() + this->getHeaders() + HttpRequest::separator + this->_content + HttpRequest::separator;

  std::cout << fRequest << std::endl;
  return (fRequest);
}
