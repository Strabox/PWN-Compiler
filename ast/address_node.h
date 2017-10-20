#ifndef __PWN_AST_ADDRESS_NODE_H__
#define __PWN_AST_ADDRESS_NODE_H__

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing address of left-values.
   */
  class address_node: public cdk::unary_expression_node {

  std::string _name = "address_node";
  	  
  public:
    
    inline address_node(int lineno, cdk::expression_node *left_value) :
        cdk::unary_expression_node(lineno, left_value) {
    }

    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_address_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
 
