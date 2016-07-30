#include "ParseJson.h"

ParseJson::ParseJson()
{
  _expression = ( no_node_d[ch_p('{')] >> *(_line)  >> no_node_d[ch_p('}')]
		  | no_node_d[ch_p('[')] >> *(_line)  >> no_node_d[ch_p(']')]);
			
  _line = ( !(_key >> no_node_d[ch_p(':')]) 
	    >> _value 
	    >> no_node_d[!ch_p(',')] );
			
  _key =  ( no_node_d[ch_p('\"')] 
	    >> token_node_d[+(alnum_p | ch_p('_'))] 
	    >> no_node_d[ch_p('\"')]);

  _value = ( no_node_d[ch_p('\"')]
	     >> token_node_d[ *(str_p("\\\"") | ~ch_p('\"'))]
	     >> no_node_d[ch_p('\"')]
	     | token_node_d[+digit_p]
	     | token_node_d[str_p("true")]
	     | token_node_d[str_p("false")]
	     | token_node_d[str_p("null")]
	     | _expression );
}

ParseJson::~ParseJson()
{}
