#ifndef __PWN_AST_DEF_FUNCTION_NODE_H__
#define __PWN_AST_DEF_FUNCTION_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/sequence_node.h>
#include <string>

namespace pwn {

  /**
   * Def_function_node represents function definition.
   */
  class def_function_node: public cdk::basic_node {
  
  /* Option represents if the function is private/public to the module.*/
  bool _isLocal;
  
  // Represents function's return type.
  basic_type* _type;
  
  // Node represents function's name.
  std::string _id;
  
  // Node represents arguments.
  cdk::sequence_node *_arguments;
  
  // If there is default return;
  cdk::expression_node *_default_return;
  
  // Node represents function's body.
  cdk::basic_node *_body;
  
  std::string _name = "def_function_node";
  
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline def_function_node(int lineno,bool isLocal,basic_type *type1,std::string *id,cdk::sequence_node *args,cdk::expression_node *default_return,cdk::basic_node *body) : 
    cdk::basic_node(lineno),_isLocal(isLocal),_type(type1),_id(*id),_arguments(args),_default_return(default_return),_body(body) {
    }
	
	inline bool isLocal(){
		return _isLocal;
	}
	
	inline basic_type* type(){
		return _type;
	}
	
	inline std::string id(){
		return _id;
	}
	
	inline cdk::sequence_node* arguments(){
		return _arguments;
	}
	
	inline cdk::expression_node* defaultReturn(){
		return _default_return;
	}
	
	inline cdk::basic_node* body(){
		return _body;
	}
	
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_def_function_node(this, level);
    }
	  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
