// $Id: print_node.h,v 1.3 2015/04/12 12:51:07 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_PRINTNODE_H__
#define __PWN_PRINTNODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
	  
    cdk::expression_node *_argument;

  std::string _name = "print_node";
  
  public:
    inline print_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
