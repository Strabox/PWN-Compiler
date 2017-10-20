#ifndef __PWN_AST_STOP_NODE_H__
#define __PWN_AST_STOP_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/integer_node.h>

namespace pwn {

  /**
   Stop_node node represents the instruction
   * stop of the language in loops.
   */
  class stop_node: public cdk::basic_node {
   
  // Represents the index of inner loop that should be stopped.
  unsigned int _inner_loop;

  std::string _name = "stop_node";
  
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */
     
    inline stop_node(int lineno,cdk::integer_node *loop) :
        cdk::basic_node(lineno), _inner_loop(loop->value()){
    }
    
    inline stop_node(int lineno):
		cdk::basic_node(lineno),_inner_loop(1){}
	
	inline unsigned int loop() {
      return _inner_loop;
    }
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_stop_node(this, level);
    }
    
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
