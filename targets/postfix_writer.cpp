// $Id: postfix_writer.cpp,v 1.56 2015/05/19 23:05:53 ist176102 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include <stack>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/stack_evaluator.h"
#include "ast/all.h"  // all.h is automatically generated


/*This one will be useful.
* Used to know if we are in global context or inside a function.
*/
bool globalContext = true;
/* UNUSED - Used to know if im declaring a constant or not. */
bool globalConstantDeclaraion = false;
/* USED - to pass local RODATA Labels to true labels.*/
std::string localRoDataLabel = "";

/* Used to know what label create in strings and double global declarations.*/
int stringDoubleLabel;
/* Indicates what is the current function we are compiling */
pwn::def_function_node * compilingFunction = nullptr;

int functionArgumentsOffset;
int localVariablesOffset;

/* Labels for flow control in cycles control. */
std::vector<std::string> stopLabels;
std::vector<std::string> nextLabels;

/* Used to know the amount of local bytes needed for node in stack. */
inline int calculateSize(cdk::basic_node *node){
	pwn::stack_evaluator se(node);
	return se.getBytes();
}

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

/* DONE - andre*/
void pwn::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//------------------------- LITERALS -----------------------------------

/* DONE - miguel*/
void pwn::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  if(globalContext){ //If its global write it in memory directly.
	_pf.CONST(node->value());  
  }
  else {				// This make a push to the stack normally.
	_pf.INT(node->value()); 
  }
}

/* NEAR-DONE -*/
void pwn::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl1;
	
	_pf.RODATA(); 
	 _pf.ALIGN(); 						
	_pf.LABEL(mklbl(lbl1 = ++_lbl));
	_pf.ADDR(mklbl(lbl1 = ++_lbl));
	if(!globalContext){
	  /*  leave the address on the stack */
	  _pf.TEXT(); 						
	  _pf.ADDR(mklbl(lbl1)); 			
	}
	else{
		if(globalConstantDeclaraion){
			localRoDataLabel = mklbl(lbl1);
		}
		else{	//Non Constant Global
			_pf.DATA();
			_pf.ID(mklbl(lbl1));
		}
	}
}

/* PARTIAL-DONE - andre*/
void pwn::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	int myLbl = ++_lbl;
	
	if(globalContext){
		if(globalConstantDeclaraion){
			_pf.DOUBLE(node->value());
			return;
		}
		else {
			_pf.DOUBLE(node->value());
			return;
		}
	}
	/* Load local doubles to the stack. */
	_pf.RODATA();
	_pf.ALIGN();
	_pf.LABEL(mklbl(myLbl));
	_pf.DOUBLE(node->value());
	_pf.TEXT();
	_pf.ALIGN();
	_pf.ADDR(mklbl(myLbl));
	_pf.DLOAD();	
	
}

//----------------------- UNARY EXPRESSIONS ----------------------------

/* FIX-ME - miguel*/
void pwn::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); 	// determine the value

  _pf.INT(0);
  _pf.EQ();
}

/* FIX-ME - andre*/
void pwn::postfix_writer::do_address_node(pwn::address_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this,lvl);
}

/* DONE - miguel*/
void pwn::postfix_writer::do_identity_node(pwn::identity_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this,lvl+1);
}

/* NEAR-DONE - andre*/
void pwn::postfix_writer::do_symmetric_node(pwn::symmetric_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this,lvl);
	if(node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.DNEG(); // If it is a Double, DNEG
	}
	else {
		_pf.NEG();	// Otherwise, its a NEG
	}
}

//---------------------- BINARY EXPRESSIONS ----------------------------

/* TO DO */
void pwn::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.ADD();
		return;
  }
  if( node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
	node->left()->type()->name() == basic_type::TYPE_DOUBLE){
	  //at least one is a double, making the result a double
	  node->left()->accept(this, lvl);
	  if(node->left()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	  }
	  node->right()->accept(this, lvl);
	  if(node->right()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	  }
	  //had to make both a double
	  //finally, we add
	  _pf.DADD();
	  return;
  }
  //do pointer + int
}
/* TO DO */
void pwn::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.SUB();
		return;
  }
  if( node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
	node->left()->type()->name() == basic_type::TYPE_DOUBLE){
	  //at least one is a double, making the result a double
	  node->left()->accept(this, lvl);
	  if(node->left()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	  }
	  node->right()->accept(this, lvl);
	  if(node->right()->type()->name() == basic_type::TYPE_INT){
		_pf.I2D();
	  }
	  //had to make both a double
	  //finally, we subtract
	  _pf.DSUB();
	  return;
  }
  // do pointer - pointer
}
/* DONE */
void pwn::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple multiplication
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.MUL();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  //finally, we multiply
  _pf.DMUL();
}
/* DONE */
void pwn::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple division
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.DIV();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  //finally, we divide
  _pf.DDIV();
}
/* DONE */
void pwn::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
/* DONE */
void pwn::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple less than
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.LT();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // left less than right makes it <0
  _pf.INT(0);
  // if indeed <0, then it makes it true, else, false
  _pf.LT();
}
/* DONE */
void pwn::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple less equals
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.LE();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // left less equals right makes it <=0
  _pf.INT(0);
  // if indeed <=0, then it makes it true, else, false
  _pf.LE();
}
/* DONE */
void pwn::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple greater than
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.GE();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // left greater equals right makes it >=0
  _pf.INT(0);
  // if indeed >=0, then it makes it true, else, false
  _pf.GE();
}
/* DONE */
void pwn::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple greater than
  if( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.GT();
		return;
  }
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // left greater than right makes it >0
  _pf.INT(0);
  // if indeed >0, then it makes it true, else, false
  _pf.GT();
}
/* DONE */
void pwn::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple not equals
  if(( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT) ||
	  ( node->right()->type()->name() == basic_type::TYPE_POINTER &&
	  node->left()->type()->name() == basic_type::TYPE_POINTER) ){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.NE();
		return;
  }
  
  //if it's doubles or double and int
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // different makes it < or > 0
  _pf.INT(0);
  // if indeed !=0, then it makes it true, else, false
  _pf.NE();
}
/* DONE */
void pwn::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  //simple equals
  if(( node->right()->type()->name() == basic_type::TYPE_INT &&
	  node->left()->type()->name() == basic_type::TYPE_INT) ||
	  ( node->right()->type()->name() == basic_type::TYPE_POINTER &&
	  node->left()->type()->name() == basic_type::TYPE_POINTER) ){
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.EQ();
		return;
  }
  
  //if it's doubles or double and int
  node->left()->accept(this, lvl);
  if(node->left()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  node->right()->accept(this, lvl);
  if(node->right()->type()->name() == basic_type::TYPE_INT){
	_pf.I2D();
  }
  //had to make both a double
  _pf.DCMP();
  // equals makes it =0
  _pf.INT(0);
  // if indeed =0, then it makes it true, else, false
  _pf.EQ();
}

void pwn::postfix_writer::do_and_node(pwn::and_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl = ++_lbl;

	node->left()->accept(this, lvl);
	_pf.DUP();
	_pf.JZ(mklbl(lbl));

	node->right()->accept(this, lvl);

	_pf.AND();

	_pf.LABEL(mklbl(lbl));
}

void pwn::postfix_writer::do_or_node(pwn::or_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl = ++_lbl;

	node->left()->accept(this, lvl);
	_pf.DUP();
	_pf.JNZ(mklbl(lbl));

	node->right()->accept(this, lvl);

	_pf.OR();

	_pf.LABEL(mklbl(lbl));
}

//---------------------------------------------------------------------------

/* DONE*/
void pwn::postfix_writer::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	node->lvalue()->accept(this, lvl);
	if(node->lvalue()->type()->name()== basic_type::TYPE_DOUBLE)
	  _pf.DLOAD();
	else
	  _pf.LOAD();

}

//---------------------------------------------------------------------------

/* PARTIAL-DONE - andre*/
void pwn::postfix_writer::do_variable_node(pwn::variable_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	const std::string &id = node->value();
	std::shared_ptr<pwn::symbol> symbol =_symtab.find(id);
	if(!symbol->islocal())
		_pf.ADDR(node->value());
	else
		_pf.LOCAL(symbol->addr());
}

/* DONE */
void pwn::postfix_writer::do_variable_decl_node(pwn::variable_decl_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	const std::string &id = node->value();
	//function arguments
	if(node->isFuncDecl()){
	  // the offset is increased after adding it to the argument stack section
	  // type, name, offset, local, global, function
	  _symtab.insert(node->value(),std::make_shared<pwn::symbol>(
	    node->type(), node->value(), functionArgumentsOffset, true
	  ,false,false));
	  functionArgumentsOffset += node->type()->size();
	  return;
	}
	
	//imported, implies global context (granted by grammar)
	if(node->isImported()){
	  _pf.EXTERN(id);
	  _symtab.insert(node->value(),std::make_shared<pwn::symbol>(
	    node->type(), node->value(),0, false,false,false
	  ));
	  return;
	}
	
	if(!globalContext){			//LOCAL VARIABLES
		localVariablesOffset = localVariablesOffset - node->type()->size();
		_symtab.insert(id,std::make_shared<pwn::symbol>(
				node->type(),id,localVariablesOffset,true));
		if(!node->constant()){
			if(node->init() != nullptr){
				node->init()->accept(this,lvl);
				_pf.LOCAL(localVariablesOffset);
				if(node->type()->name() == basic_type::TYPE_DOUBLE){
					_pf.DSTORE();
				}
				else{
					_pf.STORE();
				}
			}
			else{
				if(node->type()->name() != basic_type::TYPE_DOUBLE){
				  _pf.INT(0);
				  _pf.LOCAL(localVariablesOffset);
				  _pf.STORE();
				}
			}
		}
	}
	else{							//GLOBAL						
		if (node->init() == NULL) { // UNITIALIZED VARIABLES
			_pf.BSS(); 
			_pf.ALIGN(); 
			if(!node->isLocal())
				_pf.GLOBAL(id,_pf.OBJ());
			_pf.LABEL(id); 			
			_pf.BYTE(node->type()->size());	
		}
		else if(node->constant()){	//CONSTANT
			if(node->type()->name() == basic_type::TYPE_INT ||
			   node->type()->name() == basic_type::TYPE_DOUBLE){
				_pf.RODATA();
				_pf.ALIGN();
				if(!node->isLocal())
					_pf.GLOBAL(id,_pf.OBJ());
				_pf.LABEL(id);
			}
			globalConstantDeclaraion = true;
			node->init()->accept(this,lvl);
			globalConstantDeclaraion = false;
			if(node->type()->name() != basic_type::TYPE_INT &&
			   node->type()->name() != basic_type::TYPE_DOUBLE){
				_pf.RODATA();
				_pf.ALIGN();
				if(!node->isLocal())
					_pf.GLOBAL(id,_pf.OBJ());
				_pf.LABEL(id);
				_pf.ID(localRoDataLabel);
			}
		}
		else {					//NON CONSTANT HAS INITIALIZATION
			_pf.DATA();
			_pf.ALIGN();
			if(!node->isLocal())
				_pf.GLOBAL(id,_pf.OBJ());
			_pf.LABEL(id);
			node->init()->accept(this,lvl);
		}
		_pf.TEXT();
		_symtab.insert(id,std::make_shared<pwn::symbol>(node->type(),id,0,false,false,false));
	}
}

//---------------------------------------------------------------------------

/* DONE */
void pwn::postfix_writer::do_assignment_node(pwn::assignment_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	
	//type conversion!
	if((node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE) &&
	(node->rvalue()->type()->name() == basic_type::TYPE_INT)){
		node->rvalue()->accept(this, lvl); 	// determine the new value
		_pf.I2D();
		_pf.DDUP();
		node->lvalue()->accept(this, lvl); 	// where to store the value
		_pf.DSTORE();
		return;
	}
	//no type conversion:
	node->rvalue()->accept(this, lvl); 	// determine the new value
	if(node->rvalue()->type()->name() != basic_type::TYPE_DOUBLE)
	  _pf.DUP(); 						// store the value at address
	else
	  _pf.DDUP();
	node->lvalue()->accept(this, lvl); 	// where to store the value
	if(node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE)
	  _pf.STORE(); 						// store the value at address
	else
	  _pf.DSTORE();
}	

//---------------------------------------------------------------------------

/* DONE */
void pwn::postfix_writer::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  }
   else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.TRASH(4);
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.TRASH(8); // delete the evaluated value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
   //EMPTY
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

/* PARTIAL-DONE - andre*/
void pwn::postfix_writer::do_print_node(pwn::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.EXTERN("printi");
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
	_pf.EXTERN("prints");
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
	_pf.EXTERN("printd");  
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
   //EMPTY
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

/* PARTIAL-DONE - miguel*/
void pwn::postfix_writer::do_printline_node(pwn::printline_node * const node, int lvl) { 
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
	_pf.EXTERN("printi");  
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
	_pf.EXTERN("prints");  
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
	_pf.EXTERN("printd");  
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
	//EMPTY
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.EXTERN("println");
  _pf.CALL("println"); // print a newline 
}

//---------------------------------------------------------------------------

/* FIX-ME - andre*/
void pwn::postfix_writer::do_read_node(pwn::read_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  if(node->type()->name() == basic_type::TYPE_INT){
	  _pf.EXTERN("readi");
	  _pf.CALL("readi");
	  _pf.PUSH();
  }else if(node->type()->name() == basic_type::TYPE_DOUBLE){
	  _pf.EXTERN("readd");
	  _pf.CALL("readd");
	  _pf.DPUSH();
  }
}

//---------------------------------------------------------------------------

void pwn::postfix_writer::do_while_node(cdk::while_node * const node, int lvl) {
  //EMPTY - NOT USED IN PWN...
}

/* DONE - */
void pwn::postfix_writer::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  int lbl1, lbl2,lbl3;
  lbl1 = ++_lbl;
  lbl2 = ++_lbl;
  lbl3 = ++_lbl;
  std::string stop = mklbl(lbl2);
  std::string next = mklbl(lbl3);
  stopLabels.push_back(stop);
  nextLabels.push_back(next);
  
  node->init()->accept(this,lvl);
  _pf.LABEL(mklbl(lbl1));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2));
  node->block()->accept(this, lvl);
  _pf.LABEL(mklbl(lbl3));
  node->incr()->accept(this,lvl);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
  
  stopLabels.pop_back();
  nextLabels.pop_back();
}

//----------
void pwn::postfix_writer::do_apply_node(pwn::apply_node * const node, int lvl) {
  int lbl1, lbl2,lbl3;
  lbl1 = ++_lbl;
  lbl2 = ++_lbl;
  lbl3 = ++_lbl;
  std::string stop = mklbl(lbl2);
  std::string next = mklbl(lbl3);
  
  
  node->vector()->accept(this,lvl);
  node->low()->accept(this,lvl);
  _pf.LABEL(mklbl(lbl1));
  _pf.ADDR
  node->high()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2));
  node->block()->accept(this, lvl);
  _pf.LABEL(mklbl(lbl3));
  node->incr()->accept(this,lvl);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
  
  
}
//----------
//---------------------------------------------------------------------------

/* DONE - DONE BY PROFESSOR. */
void pwn::postfix_writer::do_if_node(cdk::if_node * const node, int lvl) {
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

/* DONE - DONE BY PROFESSOR. */
void pwn::postfix_writer::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//---------------------------------------------------------------------------

/* DONE */
void pwn::postfix_writer::do_stop_node(pwn::stop_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	if(node->loop() > stopLabels.size()){
		std::cerr << "Not enough inner cycles to use stop" <<std::endl;
		return;
	}
	_pf.JMP(stopLabels[stopLabels.size() - node->loop()]); 
}

/* DONE */
void pwn::postfix_writer::do_next_node(pwn::next_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	if(node->loop() > stopLabels.size()){
		std::cerr << "Not enough inner cycles to use stop" <<std::endl;
		return;
	}
	_pf.JMP(nextLabels[nextLabels.size() - node->loop()]); 
}

/* DONE */
void pwn::postfix_writer::do_return_node(pwn::return_node * const node, int lvl) {
	if(compilingFunction == nullptr) {
		std::cerr << "ERRO: Return outside function" << std::endl;
		exit(1);
	}
	if(compilingFunction->type()->name() == basic_type::TYPE_INT ||
	   compilingFunction->type()->name() == basic_type::TYPE_STRING ||
	   compilingFunction->type()->name() == basic_type::TYPE_POINTER){
	   _pf.LOCV(-4);
	   _pf.POP();
	}
	else if(compilingFunction->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.LOCAL(-8);
		_pf.DLOAD();
		_pf.DPOP();
	}
	_pf.LEAVE();
	_pf.RET();
}

/* DONE - andre */
void pwn::postfix_writer::do_function_call_node(pwn::function_call_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	size_t argsSize = 0;
	
	if(node->arguments() != nullptr){
		node->arguments()->accept(this,lvl);
		// FIXME This down cast could be dangerous!!!
		// Calculate the arguments size to destroy after the call.
		for(size_t i = 0; i < node->arguments()->size(); i++){
			cdk::expression_node *nodei = (cdk::expression_node*) node->arguments()->node(i);
			argsSize += nodei->type()->size();
		}
	}
	_pf.CALL(node->id());
	_pf.TRASH(argsSize);	//Clear arguments from stack.
	
	const std::string &id = node->id();
	std::shared_ptr<pwn::symbol> s = _symtab.find(id);
	
	if(s->type()->name() == basic_type::TYPE_INT ||
	   s->type()->name() == basic_type::TYPE_STRING ||
	   s->type()->name() == basic_type::TYPE_POINTER)
	   _pf.PUSH();		//Bring to stack from eax(register) the return (4 bytes).
	else if(s->type()->name() == basic_type::TYPE_DOUBLE)
		_pf.DPUSH();	//Bring to stack from st0(register) the return (8 bytes).
}

/* DONE - andre */
void pwn::postfix_writer::do_def_function_node(pwn::def_function_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);	
	
	std::string funcName = node->id();
	// (RTS mandates that its name be "_main")
	if(funcName == "pwn"){ 
		funcName = "_main";
	}
	else if(funcName == "_main") funcName = "._main";
	
	_pf.TEXT();
	if(!node->isLocal())
		_pf.GLOBAL(funcName, _pf.FUNC());
	_pf.ALIGN();
	_pf.LABEL(funcName);
	
	_symtab.push();
	globalContext = false;
	compilingFunction = node;
	functionArgumentsOffset = 8;
	localVariablesOffset = - (node->type()->size());

	if(node->arguments() != NULL)
		node->arguments()->accept(this,lvl);
	
	int size = calculateSize(node);
	_pf.ENTER(size);  	
	//Put the default return in return's variable.
	if(node->type()->name() != basic_type::TYPE_VOID){
		_symtab.insert(node->id(),std::make_shared<pwn::symbol>(node->type()
				,node->id(),localVariablesOffset,true,false,false));
		if(node->defaultReturn() != nullptr){		//WITH INIT
			node->defaultReturn()->accept(this,lvl);
			if(node->defaultReturn()->type()->name() == basic_type::TYPE_DOUBLE){
				_pf.LOCAL(-8);
				_pf.DSTORE();
			}
			else{
				_pf.LOCAL(-4);
				_pf.STORE();
			}	
		}
		else{										//DEFAULT INIT
			if(node->type()->name() != basic_type::TYPE_DOUBLE &&
				node->type()->name() != basic_type::TYPE_STRING){
				_pf.INT(0);
				_pf.LOCAL(-4);
				_pf.STORE();
			}	
		}	
	}
	//Finally generate the body....
	node->body()->accept(this, lvl);

	if(node->type()->name() == basic_type::TYPE_DOUBLE){
		_pf.LOCAL(-8);
		_pf.DLOAD();
		_pf.DPOP();
	}
	else{
		_pf.LOCV(-4);
		_pf.POP();
	}
	_pf.LEAVE();
	_pf.RET();
	
	_symtab.pop();
	compilingFunction = nullptr;
	globalContext = true;
}

/* DONE  */
void pwn::postfix_writer::do_decl_function_node(pwn::decl_function_node * const node, int lvl) {
	// Check if there is already one declaration with same name.
	std::shared_ptr<pwn::symbol> s = _symtab.find(node->id());
	if(s != nullptr)
		throw std::string("Error symbol already declared");
	else{
		if(node->isImported() || node->id() == "argc" || node->id() =="argv"){
			_symtab.insert(node->id(),std::make_shared<pwn::symbol>(node->type(),
			node->id(),0,false,true,true));
			_pf.EXTERN(node->id());
		}
		else{
			_symtab.insert(node->id(),std::make_shared<pwn::symbol>(node->type(),
			node->id(),0,false,true,false));
		}
	}
}

/* DONE */
void pwn::postfix_writer::do_block_node(pwn::block_node * const node, int lvl) {
	_symtab.push();
	if(node->declarations() != NULL)
		node->declarations()->accept(this,lvl);
	if(node->instructions() != NULL){
		node->instructions()->accept(this,lvl); 
	}
	if(node->ret() != NULL){
	  node->ret()->accept(this, lvl);
	}
	_symtab.pop();
}

/* DONE  */
void pwn::postfix_writer::do_index_node(pwn::index_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->total()->accept(this,lvl);	//Base address.
  _pf.LOAD();
  node->shift()->accept(this,lvl);	//Number of position from base.
  _pf.INT(8);						//DOUBLE size
  _pf.MUL();
  _pf.ADD();
}

/* DONE */
void pwn::postfix_writer::do_noob_node(pwn::noob_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	if(!globalContext)
		_pf.INT(0);
	else
		_pf.CONST(0);
}

/* DONE */
void pwn::postfix_writer::do_memory_alloc_node(pwn::memory_alloc_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
	_pf.INT(8);							//DOUBLE size
	node->argument()->accept(this,lvl);	//How many doubles ?
	_pf.MUL();
	_pf.ALLOC();
	_pf.SP();
	
}

//---------------------------------------------------------------------------

