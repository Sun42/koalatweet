#ifndef __PARSECOMMON_H__
#define __PARSECOMMON_H__

#include <iostream>
#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/tree/tree_to_xml.hpp>

#include "ExceptionTweet.h"

using namespace boost::spirit;

typedef char const*         iterator_t;
typedef tree_match<iterator_t> parse_tree_match_t;
typedef parse_tree_match_t::const_tree_iterator iter_t;

typedef pt_match_policy<iterator_t> match_policy_t;
typedef scanner_policies<iteration_policy, match_policy_t, action_policy> scanner_policy_t;
typedef scanner<iterator_t, scanner_policy_t> scanner_t;
typedef rule<scanner_t> rule_t;

class	ParseCommon
{
public:
  ParseCommon();
  ~ParseCommon();

  void	parse(char const *);
  void	affTree(char const * first) const;
  void	getId(std::vector<std::string> & ids) const;
  std::string	getFrom(std::string const & key) const;
  std::string   getHttpContent() const;
  void		getInfoUser(std::map<std::string, std::string> & infoUser) const;
  bool		isHttpFull() const;

protected:
  std::string	_getValue(iter_t const & node) const;
  void		_genInfoUser(iter_t const & expr,std::map<std::string, std::string> & infoUser) const;

  rule_t _expression, _line, _key, _value;
  tree_parse_info<> _info;

private:
  ParseCommon & operator=(ParseCommon const &);
  ParseCommon(ParseCommon const &);

};

#endif /* !__PARSECOMMON_H__ */
