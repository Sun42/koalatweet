#ifndef ApiTwitter_H
#define ApiTwitter_H

#include <QMap>
#include <QString>

class	ApiTwitter
{
 public:
  typedef void (ApiTwitter::*funcPtr)(QString & cmd);

  static ApiTwitter*	getInstance();
  static void		destroyInstance();
  void			execCmd(int func, QString cmd);
  void                  setAuth(QString const & auth);
  void                  setLogs(QString const & logs);
  static const QString  _host;

 private:
  ~ApiTwitter();
  ApiTwitter();
  ApiTwitter(ApiTwitter const &);
  ApiTwitter &	operator=(ApiTwitter const &);
  void			auth(QString& cmd);

 private:
  static ApiTwitter*	_instance;
  QMap<int, funcPtr>	_funcCaller;
  QString               _auth;
  QString               _logs;
};

#endif // ApiTwitter_H
