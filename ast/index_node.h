// $Id: index_node.h,v 1.8 2015/05/16 13:22:45 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_AST_INDEX_NODE_H__
#define __PWN_AST_INDEX_NODE_H__

#include <cdk/ast/expression_node.h>
#include "variable_node.h"

namespace pwn {

  /**
   * Index_node - Class for describe memory indexation.
   */
  class index_node: public variable_node {
   
    cdk::expression_node* _total;
    
    cdk::expression_node* _shift;
    
    std::string _name="index_node";
    
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline index_node(int lineno,std::string *id,cdk::expression_node *total,cdk::expression_node *shift) : 
		variable_node(lineno,id), _total(total),_shift(shift){
    }
    
    inline index_node(int lineno,cdk::expression_node *total,cdk::expression_node *shift):
		variable_node(lineno), _total(total),_shift(shift){}
	    
    inline cdk::expression_node* total(){
      return _total;
    }

    inline cdk::expression_node* shift(){
      return _shift;
    }
    
      void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }
	
    std::string name(){
      return _name;
    }
    
  };

} // pwn

#endif 
