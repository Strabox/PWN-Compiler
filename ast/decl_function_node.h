#ifndef __PWN_AST_DECL_FUNCTION_NODE_H__
#define __PWN_AST_DECL_FUNCTION_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/sequence_node.h>
#include <string>

namespace pwn {

  /**
   * Decl_function_node represents function declaration.
   */
  class decl_function_node: public cdk::basic_node {
  
  /* Option represents if the function is private/public to the module.*/
  bool _isLocal;
  
   /* Option represents if the function is imported or not*/
  bool _isImported;
  
  // represents function's return type.
  basic_type *_type;
  
  // Node represents function's name.
  std::string _id;
  
  // Node represents function arguments.
  cdk::sequence_node *_arguments;
  
  // Node represents default return.
  cdk::expression_node* _default_return;
  
  std::string _name = "decl_function_node";
  
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */ 
    inline decl_function_node(int lineno,bool isLocal,bool isImported,basic_type* type1,std::string *id,cdk::sequence_node *args,cdk::expression_node* default_return) : 
    cdk::basic_node(lineno),_isLocal(isLocal),_isImported(isImported),_type(type1),_id(*id),_arguments(args),_default_return(default_return) {
    }
	
	inline bool isLocal(){
		return _isLocal;
	}
	
	inline bool isImported(){
		return _isImported;
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
	
	void accept(basic_ast_visitor *sp, int level) {
      sp->do_decl_function_node(this, level);
    }
	  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif
