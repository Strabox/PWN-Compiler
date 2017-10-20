// $Id: printline_node.h,v 1.5 2015/04/13 20:13:55 ist176046 Exp $ -*- c++ -*-
#ifndef __PWN_PRINTLINE_NODE_H__
#define __PWN_PRINTLINE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing printline nodes.
   */
  class printline_node: public cdk::basic_node {
	  
    cdk::expression_node *_argument;
    
    std::string _name = "printline_node";

  public:
    inline printline_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_printline_node(this, level);
    }
    std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
