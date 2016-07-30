#include "ParseHttp.h"

ParseHttp::ParseHttp()
{
  _expression = (*(_line));
  _line =(_key >> no_node_d[!(ch_p(':') | ch_p(',')) >> ch_p(' ')] 
	  >> _value >> no_node_d[str_p("\r\n")]
	  | no_node_d[str_p("\r\n")] >> _value);

  _key = ( token_node_d[str_p("GET")]
	   | token_node_d[str_p("POST")]
	   | token_node_d[str_p("HTTP") >> (ch_p('/') | ch_p(' ')) >> real_p]
	   | token_node_d[+(alnum_p | ch_p('-') | ch_p('_'))]
	   );

  _value = (token_node_d[+print_p]);
}

ParseHttp::~ParseHttp()
{}
