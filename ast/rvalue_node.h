// $Id: rvalue_node.h,v 1.3 2015/04/13 14:49:34 ist176046 Exp $
#ifndef __PWN_RVALUE_NODE_H__
#define __PWN_RVALUE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing rvalue nodes.
   */
  class rvalue_node: public cdk::expression_node {
	  
    pwn::lvalue_node *_lvalue;
    
    std::string _name = "rvalue_node";

  public:
    inline rvalue_node(int lineno, pwn::lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_rvalue_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
