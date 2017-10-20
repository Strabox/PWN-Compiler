#ifndef __PWN_AST_NEXT_NODE_H__
#define __PWN_AST_NEXT_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/integer_node.h>

namespace pwn {

  /**
   Stop_node node represents the instruction
   * stop of the language in loops.
   */
  class next_node: public cdk::basic_node {
   
   // Expression represents what cycle we will restart.
  unsigned int _loop;

  std::string _name = "next_node";
  
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */
     
    inline next_node(int lineno,cdk::integer_node* loop) :
        cdk::basic_node(lineno), _loop(loop->value()){
    }
    
    inline next_node(int lineno) :
        cdk::basic_node(lineno), _loop(1){
    }
	
	inline unsigned int loop() {
      return _loop;
    }
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_next_node(this, level);
    }

      
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
