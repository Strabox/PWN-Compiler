#ifndef __PWN_AST_SYMMETRIC_NODE_H__
#define __PWN_AST_SYMMETRIC_NODE_H__

#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Symmetric_node - Node for describing symmetric in expressions.
   */
  class symmetric_node: public cdk::unary_expression_node {

    std::string _name = "symmetric_node";

  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline symmetric_node(int lineno, cdk::expression_node *arg) : 
		cdk::unary_expression_node(lineno, arg){
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_symmetric_node(this, level);
    }
    
    std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
  
