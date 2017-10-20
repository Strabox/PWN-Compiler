#ifndef __PWN_AST_RETURN_NODE_H__
#define __PWN_AST_RETURN_NODE_H__

#include <cdk/ast/basic_node.h>

namespace pwn {

  /**
   * Return_node represents return instruction
   * used to leave/return from functions.
   */
  class return_node: public cdk::basic_node {
     std::string _name = "return_node";
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline return_node(int lineno) : cdk::basic_node(lineno){
    }
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }
    
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
