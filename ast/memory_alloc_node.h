// $Id: memory_alloc_node.h,v 1.2 2015/04/12 12:51:07 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_AST_MEMORY_ALLOC_NODE_H__
#define __PWN_AST_MEMORY_ALLOC_NODE_H__

#include <cdk/ast/unary_expression_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   Memory_alloc_node nodes represents memory allocation.
   */
  class memory_alloc_node: public cdk::unary_expression_node {


  std::string _name = "memory_alloc_node";
  
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */
     
    inline memory_alloc_node(int lineno,cdk::expression_node *expr) :
        cdk::unary_expression_node(lineno, expr){
    }
	
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_memory_alloc_node(this, level);
    }
    
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
