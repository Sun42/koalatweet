#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QString>
#include <iostream>

#include "login.h"
#include "network.h"
#include "apitwitter.h"
#include "Connection.h"

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

    public:
  static MainWindow*	getInstance();
  static void		destroyInstance();
  void			logIn(QString const & userName, QString const & pass);
  void			setAuth() const;
  void			setLogs() const;
  bool			checkProxy() const;
  void			setLogInfo(QString const & info);

  private slots:
  void			sendButProv();
  void			meClicked();
  void			favoritesClicked();
  void			followingClicked();
  void			followersClicked();
  void			publicClicked();
  void			searchesClicked();
  void			restoreMenu();
  void			loginWindow();
  void			leave();
  void			connection();
  void			addItem();

 private:
  void			logOutMode();
  void			logInMode();
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *	ui;
  static MainWindow *	_uniqueInstance;
  LoginWidget*		_loginDial;
  ApiTwitter*		_apiTwitter;
  QString		_buffer;
  QString		_login;
  QString		_pass;
  bool			_isConnect;
};

#endif // MAINWINDOW_H
