// $Id: read_node.h,v 1.3 2015/04/13 14:49:34 ist176046 Exp $ -*- c++ -*-
#ifndef __PWN_READNODE_H__
#define __PWN_READNODE_H__

#include "ast/lvalue_node.h"
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {
    
  std::string _name = "read_node";
  
  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
