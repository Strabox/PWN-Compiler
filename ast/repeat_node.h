#ifndef __PWN_REPEATNODE_H__
#define __PWN_REPEATNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Class for describing repeat-cycle nodes.
   */
  class repeat_node: public cdk::basic_node {
	
	//Initialization expression.
    cdk::expression_node *_init;
	
	//Condition expression.
    cdk::expression_node *_condition;
	
	//Increment expression.
    cdk::expression_node *_incr;
	
	//Node for instruction inside repeat.
    cdk::basic_node *_block;

      std::string _name = "repeat_node";
      
  public:
    inline repeat_node(int lineno, cdk::expression_node *init,cdk::expression_node *condition, cdk::expression_node *incr, cdk::basic_node *block) :
        basic_node(lineno),_init(init), _condition(condition), _incr(incr) ,_block(block) {
    }

  public:
    inline cdk::expression_node *init() {
      return _init;
    }
    inline cdk::expression_node *condition() {
      return _condition;
    }
    inline cdk::expression_node *incr() {
      return _incr;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_repeat_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
