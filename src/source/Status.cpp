#include "Status.h"

Status::Status(std::string& text, std::string& id, std::string& time)   : _text(text), _id(id), _createAt(time)
{
}

Status::Status(const Status& rt)
{
      this->_text = rt._text;
      this->_id = rt._id;
      this->_createAt = rt._createAt;
}

Status::~Status()
{
}

Status& Status::operator=(const Status &rt)
{
    if (this != &rt)
    {
        this->_text = rt._text;
        this->_id = rt._id;
        this->_createAt = rt._createAt;
    }
    return (*this);
}

void Status::setText(std::string& text)
{
    this->_text = text;
}

std::string Status::getText() const
{
    return (this->_text);
}

void Status::setId(std::string& id)
{
    this->_id = id;
}

std::string Status::getId() const
{
    return (this->_id);
}

void Status::setcreateAt(std::string& time)
{
    this->_createAt = time;
}

std::string Status::getcreateAt() const
{
    return (this->_createAt);
}

