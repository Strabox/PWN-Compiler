// $Id: type_checker.cpp,v 1.43 2015/05/19 21:56:11 ist176046 Exp $ -*- c++ -*-
#include <string>
#include <stack>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }


std::stack<pwn::lvalue_node*> leftValues;


//-------------------------- LITERALS ----------------------------------

/* DONE - */
void pwn::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

/* DONE - */
void pwn::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

/* DONE */
void pwn::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

//----------------------UNARY EXPRESSIONS-------------------------------

/* PARTIAL-DONE - */
inline void pwn::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
	node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE)
	node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else{
    throw std::string("Wrong type in argument of arithmetic unary expression");
   }
}

/* PARTIAL-DONE - */
void pwn::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);	
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
	node->type(new basic_type(4, basic_type::TYPE_INT));
  else
	throw std::string("Wrong type in argument of neg unary expression");
}

/* PARTIAL-DONE - */
void pwn::type_checker::do_identity_node(pwn::identity_node * const node, int lvl){
	processUnaryExpression(node, lvl);
}

/* PARTIAL-DONE - */
void pwn::type_checker::do_symmetric_node(pwn::symmetric_node * const node, int lvl){
	processUnaryExpression(node,lvl);
}

/* NEAR_DONE - andre */
void pwn::type_checker::do_address_node(pwn::address_node * const node, int lvl){
	node->argument()->accept(this, lvl);
	if(node->argument()->type()->name() != basic_type::TYPE_DOUBLE)
		throw std::string("Not addressing a real");
	node->type(new basic_type(4,basic_type::TYPE_POINTER));
}

//-----------------------BINARY EXPRESSIONS-----------------------------

/* COULD THIS BE MADE SIMPLER? -  */
inline void pwn::type_checker::processBinaryArithmeticExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else if(node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_POINTER &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_POINTER));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_POINTER){
		node->type(new basic_type(4, basic_type::TYPE_POINTER));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_POINTER &&
	  node->left()->type()->name() == basic_type::TYPE_POINTER){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else
	throw std::string("wrong combination of types in arithmetc binary expression");
}

/* COULD THIS BE MADE SIMPLER? -  */
inline void pwn::type_checker::processBinaryIntegerRealExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else if(node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else
	throw std::string("wrong combination of types in logical binary expression");
}

/* COULD THIS BE MADE SIMPLER? -  */
inline void pwn::type_checker::processBinaryEqualityExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else if(node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
  }
  else if( node->right()->type()->name() == basic_type::TYPE_POINTER &&
	  node->left()->type()->name() == basic_type::TYPE_POINTER){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else
	throw std::string("wrong combination of types in arithmetc binary expression");
}

/* PARTIAL-DONE - */
inline void pwn::type_checker::processBinaryLogicalExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
	
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else
	throw std::string("wrong combination of types in logical binary expression");	
}


/* Arithmetic Binary Expressions */
void pwn::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryArithmeticExpression(node, lvl);
}
void pwn::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryArithmeticExpression(node, lvl);
}
void pwn::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_UNSPEC;
  //very restrictive
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
		return;
  }
  else
	throw std::string("wrong combination of types in logical binary expression");
	
}
void pwn::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryIntegerRealExpression(node, lvl);
}
void pwn::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryEqualityExpression(node, lvl);
}
void pwn::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryEqualityExpression(node, lvl);
}

/* Logical Binary Expressions */

void pwn::type_checker::do_and_node(pwn::and_node * const node, int lvl) {
  processBinaryLogicalExpression(node, lvl);
}
void pwn::type_checker::do_or_node(pwn::or_node * const node, int lvl) {
  processBinaryLogicalExpression(node, lvl);
}

//---------------------------------------------------------------------------

/* DONE  */
void pwn::type_checker::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}

//---------------------------------------------------------------------------

/* DONE - True Variable Declaration*/
void pwn::type_checker::do_variable_decl_node(pwn::variable_decl_node * const node, int lvl){
	std::shared_ptr<pwn::symbol> s = _symtab.find_local(node->value());
	if( s != nullptr)
		throw std::string("Symbol already in use");
	if(node->init() != nullptr){
		node->init()->accept(this,lvl);
		if(node->init()->type()->name() != node->type()->name())
			throw std::string("Wrong type initializations");
	}
}

/* PARTIAL-DONE - This is the true form of a variable (as left-value)! */
void pwn::type_checker::do_variable_node(pwn::variable_node * const node, int lvl){
	const std::string &id = node->value();
	// Variable never declared, programmer forgot something ._.
	std::shared_ptr<pwn::symbol> symbol = _symtab.find(id);
	if (symbol == nullptr) {
		node->type(new basic_type(0, basic_type::TYPE_ERROR));
		throw std::string("Variable undeclared");
	}
	//Set the type of left value to the one registered in symbolTable.
	if(symbol->type()->name() == basic_type::TYPE_INT)
		node->type(new basic_type(4, basic_type::TYPE_INT));
	else if(symbol->type()->name() == basic_type::TYPE_DOUBLE)
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
	else if(symbol->type()->name() == basic_type::TYPE_POINTER)
		node->type(new basic_type(4, basic_type::TYPE_POINTER));
	else if(symbol->type()->name() == basic_type::TYPE_STRING)
		node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

/* PARTIAL-DONE - */
void pwn::type_checker::do_assignment_node(pwn::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->lvalue()->accept(this, lvl + 2);
  leftValues.push(node->lvalue());
  node->rvalue()->accept(this, lvl + 2);
  leftValues.pop();
  
  if((node->lvalue()->type()->name() == basic_type::TYPE_VOID)
	|| (node->rvalue()->type()->name() == basic_type::TYPE_VOID)
	|| (node->lvalue()->type()->name() == basic_type::TYPE_ERROR)
	|| (node->rvalue()->type()->name() == basic_type::TYPE_ERROR)
	|| (node->lvalue()->type()->name() == basic_type::TYPE_UNSPEC)){
	//Impossible cases.
	node->type(new basic_type(0,basic_type::TYPE_ERROR));
	return;
  }	
  else if( node->lvalue()->type()->name() == basic_type::TYPE_INT &&
	  node->rvalue()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(4, basic_type::TYPE_INT));
  }
  else if( node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->rvalue()->type()->name() == basic_type::TYPE_INT){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
  else if(node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE &&
	  node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE){
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
  else if(node->lvalue()->type()->name() == basic_type::TYPE_STRING &&
	  node->rvalue()->type()->name() == basic_type::TYPE_STRING){
		node->type(new basic_type(4, basic_type::TYPE_STRING));
  }
  else if(node->lvalue()->type()->name() == basic_type::TYPE_POINTER &&
	  node->rvalue()->type()->name() == basic_type::TYPE_POINTER){
		node->type(new basic_type(4, basic_type::TYPE_POINTER));
  }
  else{
	node->type(new basic_type(0,basic_type::TYPE_ERROR));  
	throw std::string("wrong combination of types in assignment expression");
  }
}

//---------------------------------------------------------------------------

/* PARTIAL-DONE - */
void pwn::type_checker::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl);
}

/* DONE - */
void pwn::type_checker::do_print_node(pwn::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl);
  if(node->argument()->type()->name() == basic_type::TYPE_VOID)
	throw std::string("Wrong Type in print");
}

/* DONE - */
void pwn::type_checker::do_printline_node(pwn::printline_node * const node, int lvl) {
  node->argument()->accept(this, lvl);
  if(node->argument()->type()->name() == basic_type::TYPE_VOID)
	throw std::string("Wrong Type in printline");
}

//---------------------------------------------------------------------------

/* NEAR-DONE - andre */
void pwn::type_checker::do_read_node(pwn::read_node * const node, int lvl) {
	ASSERT_UNSPEC;
	
	if(leftValues.size() == 0){		//Default One (i.e: ! and !!)
		node->type(new basic_type(4,basic_type::TYPE_INT));
		return;
	}
	pwn::lvalue_node * lval = leftValues.top();
	if(lval->type()->name() == basic_type::TYPE_INT)
		node->type(new basic_type(4,basic_type::TYPE_INT));
	else if(lval->type()->name() == basic_type::TYPE_DOUBLE)
		node->type(new basic_type(8,basic_type::TYPE_DOUBLE));
	else
		throw std::string("Wrong type do read");
}

//---------------------------------------------------------------------------

/* DONE - */
void pwn::type_checker::do_while_node(cdk::while_node * const node, int lvl) {
  /*EMPTY!!!! - Only needed to compile.*/
}

/* PARTIAL-DONE - */
void pwn::type_checker::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

/* PARTIAL-DONE - */
void pwn::type_checker::do_if_node(cdk::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

/* PARTIAL-DONE - */
void pwn::type_checker::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//--------------------------------------------------------------------------

// DONE
void pwn::type_checker::do_stop_node(pwn::stop_node * const node, int lvl) {
	// EMTPY- Dont need do nothing, its done in post_fix_writer.
}

// DONE
void pwn::type_checker::do_next_node(pwn::next_node * const node, int lvl) {
	// EMTPY- Dont need do nothing, its done in post_fix_writer.
}

void pwn::type_checker::do_return_node(pwn::return_node * const node, int lvl) {
	// EMTPY- Dont need do nothing, its done in post_fix_writer.
}

/* DONE */
void pwn::type_checker::do_decl_function_node(pwn::decl_function_node * const node, int lvl) {
	// EMTPY- Dont need do nothing, its done in post_fix_writer.
}

/* DONE */
void pwn::type_checker::do_def_function_node(pwn::def_function_node * const node, int lvl) {
	// Check if return literal is the same type the function returns.
	if(node->defaultReturn() != nullptr){
		node->defaultReturn()->accept(this,lvl);
		if(node->defaultReturn()->type()->name() != node->type()->name())
			throw std::string("Invalid default return!"); 
	}  
	// Check if there is already one declaration with same name.
	std::shared_ptr<pwn::symbol> s = _symtab.find(node->id());
	if(s == nullptr) {
		_symtab.insert(node->id(),std::make_shared<pwn::symbol>(node->type(), node->id()
		,0,false,true,true));
	} 
	else if(s->isFunction() && !s->isDefined()){
		s->isDefined(true);
	}
	else if(s->isFunction() && s->isDefined()){
		throw std::string("Invalid declaration double definition");
	}
	else
		throw std::string("Error symbol already declared!");
}

/* DONE */
void pwn::type_checker::do_block_node(pwn::block_node * const node, int lvl) {
	// EMPTY - Dont need check any types.
}

/* DONE */
void pwn::type_checker::do_index_node(pwn::index_node * const node, int lvl) {
  /* We only have pointers to DOUBLES so index of a pointer is a double */
  node->total()->accept(this,lvl);
  node->shift()->accept(this,lvl);
  if(node->total()->type()->name() != basic_type::TYPE_POINTER
	 || node->shift()->type()->name() != basic_type::TYPE_INT){
		//Avoiding future problems.
		node->type(new basic_type(0,basic_type::TYPE_ERROR));
		throw std::string("Wrong type in index base");
  }
  node->type(new basic_type(8,basic_type::TYPE_DOUBLE));
}

void pwn::type_checker::do_noob_node(pwn::noob_node * const node, int lvl) {
	node->type(new basic_type(4,basic_type::TYPE_POINTER));
}

/* DONE */
void pwn::type_checker::do_memory_alloc_node(pwn::memory_alloc_node * const node, int lvl){
	ASSERT_UNSPEC;
	//Memory alloc returns pointer to the begin of alloced block.
	if(node->argument() == nullptr){
		node->type(new basic_type(0,basic_type::TYPE_ERROR));
		return;
	}
	node->argument()->accept(this,lvl);
	if(node->argument()->type()->name() != basic_type::TYPE_INT){
		node->type(new basic_type(0,basic_type::TYPE_ERROR));
		throw std::string("Wrong type in memory alloc size");
	}
	else
		node->type(new basic_type(4,basic_type::TYPE_POINTER));
}

/* DONE */
void pwn::type_checker::do_function_call_node(pwn::function_call_node * const node, int lvl){
	std::shared_ptr<pwn::symbol> s = _symtab.find(node->id());
	if(s == nullptr){
		//Symbol Missing (Type error to prevent incoming seg faults)
		node->type(new basic_type(0, basic_type::TYPE_ERROR));
		throw std::string("Undeclared function");
	}
	if(s->type()->name() == basic_type::TYPE_INT)
		node->type(new basic_type(4,basic_type::TYPE_INT));
	else if(s->type()->name() == basic_type::TYPE_DOUBLE)
		node->type(new basic_type(8,basic_type::TYPE_DOUBLE));
	else if(s->type()->name() == basic_type::TYPE_POINTER)
		node->type(new basic_type(4,basic_type::TYPE_POINTER));
	else if(s->type()->name() == basic_type::TYPE_STRING)
		node->type(new basic_type(4,basic_type::TYPE_STRING));
	else if(s->type()->name() == basic_type::TYPE_VOID)
		node->type(new basic_type(0,basic_type::TYPE_VOID));
}
//--------------------------------------------------------------------------
