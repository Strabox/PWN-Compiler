// $Id: block_node.h,v 1.4 2015/05/18 13:25:53 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_BLOCK_NODE_H__
#define __PWN_BLOCK_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/sequence_node.h>

namespace pwn {

  /**
   * Class for describing block nodes.
   */
  class block_node: public cdk::basic_node {
	  
	// Variables and Constants declaration.
	cdk::sequence_node *_declarations;
	 
	// Set of instructions.
    cdk::sequence_node *_instructions;

  std::string _name = "block_node";
  
  cdk::basic_node* _return;
  
  public:
    inline block_node(int lineno, cdk::sequence_node *decl,cdk::sequence_node *instr, cdk::basic_node* n) :
        cdk::basic_node(lineno), _declarations(decl),_instructions(instr), _return(n) {
    }

  public:
    inline cdk::sequence_node *declarations() {
      return _declarations;
    }

    inline cdk::sequence_node *instructions() {
      return _instructions;
    }
    
    inline cdk::basic_node *ret(){
      return _return;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
