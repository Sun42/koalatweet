#ifndef HTTPREQUEST_H_
# define HTTPREQUEST_H_

#include <iostream>
#include <string>
#include <map>

class	HttpRequest
{
 public:
  static const std::string	separator;
  static const std::string	httpVersion;
  HttpRequest();
  ~HttpRequest();
  HttpRequest(HttpRequest const &);
  HttpRequest&		operator=(HttpRequest const &);
  void			setCommande(std::string );
  void			setRessource(std::string );
  void			setHeader(std::string , std::string );
  void			setContent(std::string &);

  std::string		getCommande() const;
  std::string		getHeaders() const;
  std::string		getFullRequest() const;

 private:
  std::string				_commande;
  std::string				_ressource;
  std::map<std::string, std::string>	_headers;
  std::string				_content;
};

#endif
