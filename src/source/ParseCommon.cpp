#include "ParseCommon.h"

ParseCommon::ParseCommon()
{}

ParseCommon::~ParseCommon()
{}

void	ParseCommon::parse(char const * first)
{
  _info = pt_parse(first, _expression);
  if (!_info.full)
    throw(ExceptionTweet("parsing failed"));
}

void	ParseCommon::affTree(char const * first) const
{
  if (_info.full)
    {
      std::map<parser_id, std::string> rule_names;
      rule_names[_value.id()] = "value";
      rule_names[_key.id()] = "key";
      rule_names[_line.id()] = "line";
      rule_names[_expression.id()] = "expression";
      tree_to_xml(std::cout, _info.trees, first, rule_names);
    }
  else
    {
      std::cerr << "stop : " << _info.stop << std::endl;
    }
}

std::string	ParseCommon::_getValue(iter_t const & node) const
{
  iter_t value = node->children.begin();
  std::string strValue(value->value.begin(), value->value.end());
  return strValue;
}

void	ParseCommon::getId(std::vector<std::string> & ids) const
{
  iter_t const	expr =	_info.trees.begin();
  if (expr->value.id() != _expression.id())
    throw(ExceptionTweet("getId : error expression"));

  iter_t line = expr->children.begin();
  if (line->value.id() != _line.id())
    throw(ExceptionTweet("getId : error line"));
  for (; line != expr->children.end(); ++line)
    {
      iter_t nodeValue = line->children.begin();
      if (nodeValue->value.id() != _value.id())
	throw(ExceptionTweet("getId : error expression"));
      ids.push_back(this->_getValue(nodeValue));
    }
}

std::string	ParseCommon::getFrom(std::string const & key) const
{
  iter_t const	expr =	_info.trees.begin();
  if (expr->value.id() != _expression.id())
    throw(ExceptionTweet("getFrom : error expression"));

  iter_t line = expr->children.begin();
  if (line->value.id() != _line.id())
    throw(ExceptionTweet("getFrom : error line"));
  for (; line != expr->children.end(); ++line)
    {
      iter_t nodeKey = line->children.begin();
      if (nodeKey->value.id() != _key.id())
	throw(ExceptionTweet("getFrom : error nodeKey"));
      std::string compKey = this->_getValue(nodeKey);
      if (compKey == key)
	{
	  iter_t nodeValue = ++nodeKey;
	  if (nodeValue->value.id() != _value.id())
	    throw(ExceptionTweet("getFrom : error nodeValue"));
	  return (this->_getValue(nodeValue));
	}
    }
  throw(ExceptionTweet("key not found"));
  return ("");
}

std::string	ParseCommon::getHttpContent() const
{
  iter_t const	expr =	_info.trees.begin();
  if (expr->value.id() != _expression.id())
    throw(ExceptionTweet("getHttpContent : error expression"));

  iter_t line = expr->children.begin();
  if (line->value.id() != _line.id())
    throw(ExceptionTweet("getHttpContent : error line"));
  for (; line != expr->children.end(); ++line)
    {
      iter_t nodeComp = line->children.begin();
      if (nodeComp->value.id() == _value.id())
	return (this->_getValue(nodeComp));
    }

  throw(ExceptionTweet("getHttpContent : content not found"));
  return ("");
}

void	ParseCommon::_genInfoUser(iter_t const & expr,std::map<std::string, std::string> & infoUser) const
{  
  iter_t line = expr->children.begin();
  if (line->value.id() != _line.id())
    throw(ExceptionTweet("genInfoUser : error line"));
  for (; line != expr->children.end(); ++line)
    {
      iter_t nodeKey = line->children.begin();
      if (nodeKey->value.id() != _key.id())
	throw(ExceptionTweet("genInfoUser : error nodeKey"));
      std::string nameKey = this->_getValue(nodeKey);

      iter_t nodeValue = ++nodeKey;
      if (nodeValue->value.id() != _value.id())
	throw(ExceptionTweet("genInfoUser : error nodeValue"));
      if (nodeValue->children.begin() == nodeValue->children.end())
	{
	  infoUser[nameKey] = "";
	  continue ;
	}
      if (nodeValue->children.begin()->value.id() == _expression.id())
	this->_genInfoUser(nodeValue->children.begin(), infoUser);
      else
	{
	  std::string value =  this->_getValue(nodeValue);
	  infoUser[nameKey] = "";
	  std::cout << "[" << nameKey << "] : " << value << std::endl;
	}
    }
}

void	ParseCommon::getInfoUser(std::map<std::string, std::string> & infoUser) const
{
  iter_t const	expr =	_info.trees.begin();
  if (expr->value.id() != _expression.id())
    throw(ExceptionTweet("getFrom : error expression"));
  this->_genInfoUser(expr, infoUser);
}

bool	ParseCommon::isHttpFull() const
{
  long int sizeTheo = 1;
  long int sizePrat = 2;
  try
    {
      sizeTheo = strtol(this->getFrom("Content-Length").c_str(), 0, 10);
      sizePrat = this->getHttpContent().length();
    }
  catch (ExceptionTweet & e)
    {
      return false;
    }
  if (sizeTheo == sizePrat)
    return true;
  return false;
}
