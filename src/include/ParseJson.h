#ifndef __PARSEJSON_H__
# define __PARSEJSON_H__

#include "ParseCommon.h"

class	ParseJson: public ParseCommon
{
public:
  ParseJson();
  ~ParseJson();

private:
  ParseJson(ParseJson const &);
  ParseJson &	operator=(ParseJson const &);
};

#endif /* !__PARSEJSON_H__ */
