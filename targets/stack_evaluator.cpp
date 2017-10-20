// $Id: stack_evaluator.cpp,v 1.5 2015/05/16 13:22:45 ist176102 Exp $ -*- c++ -*-
#include <string>
#include "targets/stack_evaluator.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//##################### NECESSARY ONES #################################

void pwn::stack_evaluator::do_sequence_node(cdk::sequence_node * const node, int lvl) {
	for (size_t i = 0; i < node->size(); i++) {
		node->node(i)->accept(this, lvl);
  }
}

void pwn::stack_evaluator::do_variable_decl_node(pwn::variable_decl_node * const node, int lvl){
	//Use to know a variable size (bytes).
	addBytes(node->type()->size());
}

void pwn::stack_evaluator::do_def_function_node(pwn::def_function_node * const node, int lvl) {
	if(node->type()->name() != basic_type::TYPE_VOID){
		//Calculate the return size.
		addBytes(node->type()->size());
	}
	//Calculate necessary memory for local variables in body function.
	if(node->body() != nullptr){
		node->body()->accept(this,lvl);
	}
}

void pwn::stack_evaluator::do_if_node(cdk::if_node * const node, int lvl) {
	//Calculate in if's body.
	if(node->block() != nullptr)
		node->block()->accept(this,lvl);
}

void pwn::stack_evaluator::do_if_else_node(cdk::if_else_node * const node, int lvl) {
	//Calculate in if's body and else body.
	if(node->thenblock() != nullptr)
		node->thenblock()->accept(this,lvl);
	if(node->elseblock() != nullptr)
		node->elseblock()->accept(this,lvl);
}

void pwn::stack_evaluator::do_block_node(pwn::block_node * const node, int lvl) {
	//Calculate in all block.
	if(node->declarations() != nullptr)
		node->declarations()->accept(this,lvl);
	if(node->instructions() != nullptr)
		node->instructions()->accept(this,lvl);
		
}

void pwn::stack_evaluator::do_function_call_node(pwn::function_call_node * const node, int lvl){
	//Used to know how much space we need in for arguments in stack.
	if(node->arguments() != nullptr)
		node->arguments()->accept(this,lvl);
}

void pwn::stack_evaluator::do_repeat_node(pwn::repeat_node * const node, int lvl) {
	if(node->init() != nullptr)
		node->init()->accept(this,lvl);
	if(node->block() != nullptr)
		node->block()->accept(this,lvl);
}

//##################### EMPTY ONES #####################################

void pwn::stack_evaluator::do_integer_node(cdk::integer_node * const node, int lvl) {
	
}

void pwn::stack_evaluator::do_string_node(cdk::string_node * const node, int lvl) {
    
}

void pwn::stack_evaluator::do_double_node(cdk::double_node * const node, int lvl) {
    
}

void pwn::stack_evaluator::do_neg_node(cdk::neg_node * const node, int lvl) {
	
}

void pwn::stack_evaluator::do_identity_node(pwn::identity_node * const node, int lvl){

}

void pwn::stack_evaluator::do_symmetric_node(pwn::symmetric_node * const node, int lvl){

}

void pwn::stack_evaluator::do_address_node(pwn::address_node * const node, int lvl){

}

void pwn::stack_evaluator::do_add_node(cdk::add_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_sub_node(cdk::sub_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_mul_node(cdk::mul_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_div_node(cdk::div_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_mod_node(cdk::mod_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_lt_node(cdk::lt_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_le_node(cdk::le_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_ge_node(cdk::ge_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_gt_node(cdk::gt_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_ne_node(cdk::ne_node * const node, int lvl) {
 
}
void pwn::stack_evaluator::do_eq_node(cdk::eq_node * const node, int lvl) {
}

void pwn::stack_evaluator::do_and_node(pwn::and_node * const node, int lvl) {

}
void pwn::stack_evaluator::do_or_node(pwn::or_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_variable_node(pwn::variable_node * const node, int lvl) {
	
}

void pwn::stack_evaluator::do_assignment_node(pwn::assignment_node * const node, int lvl) {
}


void pwn::stack_evaluator::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
}

void pwn::stack_evaluator::do_print_node(pwn::print_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_printline_node(pwn::printline_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_read_node(pwn::read_node * const node, int lvl) {

}


void pwn::stack_evaluator::do_while_node(cdk::while_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_stop_node(pwn::stop_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_next_node(pwn::next_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_return_node(pwn::return_node * const node, int lvl) {
	
}

void pwn::stack_evaluator::do_decl_function_node(pwn::decl_function_node * const node, int lvl) {
	
}

void pwn::stack_evaluator::do_index_node(pwn::index_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_noob_node(pwn::noob_node * const node, int lvl) {

}

void pwn::stack_evaluator::do_memory_alloc_node(pwn::memory_alloc_node * const node, int lvl){

}
