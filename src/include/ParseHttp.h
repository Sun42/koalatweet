#ifndef __PARSEHTTP_H__
# define __PARSEHTTP_H__

#include "ParseCommon.h"

class	ParseHttp: public ParseCommon
{
public:
  ParseHttp();
  ~ParseHttp();

private:
  ParseHttp(ParseHttp const &);
  ParseHttp &	operator=(ParseHttp const &);
};

#endif /* !__PARSEHTTP_H__ */
