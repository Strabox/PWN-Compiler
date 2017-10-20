#ifndef __PWN_AST_FUNCTION_CALL_NODE_H__
#define __PWN_AST_FUNCTION_CALL_NODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace pwn {

  /**
   * Index_node - Class for describe a function call.
   * It inherits from expression because a function can have return
   * values and be evaluated.
   */
  class function_call_node: public cdk::expression_node {
   
   // Function's name.
   std::string _id;
   
   // Function's arguments.
   cdk::sequence_node* _arguments;
 
  std::string _name = "function_call_node";
    
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline function_call_node(int lineno,std::string *id,cdk::sequence_node* args) : 
		cdk::expression_node(lineno),_id(*id),_arguments(args){
    }
	
	inline std::string id(){
		return _id;
	}
	
	inline cdk::sequence_node* arguments(){
		return 	_arguments;
	}
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }
	  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif  
