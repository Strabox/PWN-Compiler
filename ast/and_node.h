// $Id: and_node.h,v 1.2 2015/04/12 12:51:07 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_AST_EXPRESSION_AND_H__
#define __PWN_AST_EXPRESSION_AND_H__

#include <cdk/ast/binary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing the and ('&') operator
   */
  class and_node: public cdk::binary_expression_node {

  std::string _name = "and_node";
  
  public:
    /**
     * @param lineno source code line number for this node
     * @param left first operand
     * @param right second operand
     */
    inline and_node(int lineno, cdk::expression_node *left, cdk::expression_node *right) :
        cdk::binary_expression_node(lineno, left, right) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_and_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
