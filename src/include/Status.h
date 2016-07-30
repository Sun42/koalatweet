#ifndef STATUS_H
#define STATUS_H

#include <iostream>

class Status
{
 public:
  Status(std::string& text, std::string& id, std::string& time);
  Status(const Status& rt);
  ~Status();
  Status&	operator=(const Status &rt);
  void		setText(std::string& text);
  std::string	getText() const;
  void		setId(std::string& id);
  std::string	getId() const;
  void		setcreateAt(std::string& time);
  std::string	getcreateAt() const;

 private:
  std::string _text;
  std::string _id;
  std::string _createAt;
};

#endif // STATUS_H
