// $Id: xml_writer.cpp,v 1.24 2015/05/16 13:22:46 ist176102 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void pwn::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void pwn::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

void pwn::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void pwn::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void pwn::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

inline std::string pwn::xml_writer::convertTypeIntToString(unsigned int typeN){
  switch(typeN){
    case 1 :
      return std::string("integer");
    case 2 :
      return std::string("real");
    case 8 :
      return std::string("string");
    case 16 :
      return std::string("pointer");
    default:
      return std::string("!");
  }
}

void pwn::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void pwn::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_rvalue_node(pwn::rvalue_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_variable_node(pwn::variable_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " id='" << node->value() << "'>" << std::endl;
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_assignment_node(pwn::assignment_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------


void pwn::xml_writer::do_evaluation_node(pwn::evaluation_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_print_node(pwn::print_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_printline_node(pwn::printline_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_read_node(pwn::read_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_while_node(cdk::while_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
  /*EMPTY!!!! - Need to compile.*/
}

void pwn::xml_writer::do_repeat_node(pwn::repeat_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  // Grammar says these can be null/empty, but the parser seems to force them to exist.
  if(node->init()){
    openTag("init", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("init", lvl + 2);
  }
  if(node->condition()){
    openTag("condition", lvl + 2);
    node->condition()->accept(this, lvl + 4);
    closeTag("condition", lvl + 2);
  }
  if(node->incr()){
    openTag("incr", lvl + 2);
    node->incr()->accept(this, lvl + 4);
    closeTag("incr", lvl + 2);
  }
  if(node->block()){
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_if_node(cdk::if_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_if_else_node(cdk::if_else_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  // the if_node seems to take care of this case. just in case...
  if(node->elseblock()){
    openTag("else", lvl + 2);
    node->elseblock()->accept(this, lvl + 4);
    closeTag("else", lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_and_node(pwn::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void pwn::xml_writer::do_or_node(pwn::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void pwn::xml_writer::do_stop_node(pwn::stop_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " loop='" << std::to_string(node->loop()) << "'" << std::endl;
  closeTag(node, lvl);
}

void pwn::xml_writer::do_next_node(pwn::next_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " loop='" << std::to_string(node->loop()) << "'" << std::endl;
  closeTag(node, lvl);
}

void pwn::xml_writer::do_return_node(pwn::return_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_decl_function_node(pwn::decl_function_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " local='" << (node->isLocal() ? "true" : "false") << "' " <<
  " imported='" << (node->isImported() ? "true" : "false") << "' " <<
  " type='" << (node->type() ? convertTypeIntToString(node->type()->name()) : "!") << "'" <<
  " id='" << node->id() << "'>" << std::endl;
  if(node->arguments()){
    openTag("arguments", lvl + 2);
    node->arguments()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
  }
  if(node->defaultReturn()){
    openTag("defaultReturn", lvl + 2);
    node->defaultReturn()->accept(this, lvl + 4);
    closeTag("defaultReturn", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_def_function_node(pwn::def_function_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " local='" << (node->isLocal() ? "true" : "false") << "' " <<
  " type='" << (node->type() ? convertTypeIntToString(node->type()->name()) : "!") << "'" <<
  " id='" << node->id() << "'>" << std::endl;
  if(node->defaultReturn()){
    openTag("defaultReturn", lvl + 2);
    node->defaultReturn()->accept(this, lvl + 4);
    closeTag("defaultReturn", lvl + 2);
  }
  if(node->arguments()){
    openTag("arguments", lvl + 2);
    node->arguments()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
  }
  if(node->body()){
    openTag("body", lvl + 2);
    node->body()->accept(this, lvl + 4);
    closeTag("body", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_block_node(pwn::block_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->declarations()){
    openTag("declarations", lvl + 2);
    node->declarations()->accept(this, lvl + 4);
    closeTag("declarations", lvl + 2);
  }
  if(node->instructions()){
    openTag("instructions", lvl + 2);
    node->instructions()->accept(this, lvl + 4);
    closeTag("instructions", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_index_node(pwn::index_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->total()){
    openTag("total", lvl + 2);
    node->total()->accept(this, lvl + 4);
    closeTag("total", lvl + 2);
  }
  if(node->shift()){
    openTag("shift", lvl + 2);
    node->shift()->accept(this, lvl + 4);
    closeTag("shift", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_noob_node(pwn::noob_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_identity_node(pwn::identity_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_symmetric_node(pwn::symmetric_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_variable_decl_node(pwn::variable_decl_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " local='" << (node->isLocal() ? "true" : "false") << "' " <<
  " imported='" << (node->isImported() ? "true" : "false") << "' " <<
  " constant='" << (node->constant() ? "true" : "false") << "' " <<
  " type='" << (node->type() ? convertTypeIntToString(node->type()->name()) : "!") << "'" <<
  " id='" << node->value() << "'>" << std::endl;
  if(node->init()){
    openTag("init", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("init", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_memory_alloc_node(pwn::memory_alloc_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->argument()){
    openTag("size", lvl + 2);
    node->argument()->accept(this, lvl + 4);
    closeTag("size", lvl + 2);
  }
  closeTag(node, lvl);
}

void pwn::xml_writer::do_address_node(pwn::address_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  closeTag(node, lvl);
}

void pwn::xml_writer::do_function_call_node(pwn::function_call_node * const node, int lvl) {
  //CHECK_TYPES(_compiler, _symtab, node);
  os() << std::string(lvl, ' ') << "<" << node->name() <<
  " id='" << node->id() << "'>" << std::endl;
  if(node->arguments()){
    openTag("arguments", lvl + 2);
    node->arguments()->accept(this, lvl + 4);
    closeTag("arguments", lvl + 2);
  }
  closeTag(node, lvl);
}
//---------------------------------------------------------------------------
