#ifndef __PWN_AST_IDENTITY_NODE_H__
#define __PWN_AST_IDENTITY_NODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Identity node - class that describes the +a operand, where + makes the integer/real a positive.
   */
  class identity_node: public cdk::unary_expression_node {
   
 
  std::string _name = "identity_node";
    
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline identity_node(int lineno, cdk::expression_node *arg) : 
		cdk::unary_expression_node(lineno, arg){
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identity_node(this, level);
    }
	  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
 
