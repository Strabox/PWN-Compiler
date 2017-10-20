#ifndef __PWN_STACK_EVALUATOR_WRITER_H__
#define __PWN_STACK_EVALUATOR_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/ast/basic_node.h>
#include "targets/basic_ast_visitor.h"

namespace pwn {

  class stack_evaluator: public basic_ast_visitor {
  
  /* Value in bytes to return */
  private : size_t _bytes;
  
  public: 
    stack_evaluator(cdk::basic_node* node) : 
		basic_ast_visitor(), _bytes(0) {
		node->accept(this,0);
    }
  
    ~stack_evaluator() {
    }
  
  inline void addBytes(int bytes){
	  _bytes = _bytes + bytes;
  }
  
  inline int getBytes(){
	return _bytes;  
  }	
	  
  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
	void do_double_node(cdk::double_node * const node, int lvl);
  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);

  public:
    void do_while_node(cdk::while_node * const node, int lvl);
    void do_if_node(cdk::if_node * const node, int lvl);
    void do_if_else_node(cdk::if_else_node * const node, int lvl);

  public:
    void do_variable_node(pwn::variable_node * const node, int lvl);
    void do_rvalue_node(pwn::rvalue_node * const node, int lvl);

  public:
    void do_evaluation_node(pwn::evaluation_node * const node, int lvl);
    void do_print_node(pwn::print_node * const node, int lvl);
    void do_read_node(pwn::read_node * const node, int lvl);
    void do_assignment_node(pwn::assignment_node * const node, int lvl);
    
	/*----My new nodes methods----*/
	void do_repeat_node(pwn::repeat_node * const node,int lvl);
	void do_printline_node(pwn::printline_node * const node,int lvl);
	void do_and_node(pwn::and_node * const node,int lvl);
	void do_or_node(pwn::or_node * const node,int lvl);
	void do_stop_node(pwn::stop_node * const node,int lvl);
	void do_next_node(pwn::next_node * const node,int lvl);
	void do_return_node(pwn::return_node * const node,int lvl);
	void do_decl_function_node(pwn::decl_function_node * const node,int lvl);
	void do_def_function_node(pwn::def_function_node * const node,int lvl);
	void do_block_node(pwn::block_node * const node,int lvl);
	void do_index_node(pwn::index_node * const node,int lvl);
	void do_noob_node(pwn::noob_node * const node,int lvl);
	void do_identity_node(pwn::identity_node * const node,int lvl);
	void do_memory_alloc_node(pwn::memory_alloc_node * const node,int lvl);
	void do_symmetric_node(pwn::symmetric_node * const node,int lvl);
	void do_variable_decl_node(pwn::variable_decl_node * const node,int lvl);
	void do_address_node(pwn::address_node * const node,int lvl);
	void do_function_call_node(pwn::function_call_node * const node,int lvl);
	  
  };
  
}
#endif
