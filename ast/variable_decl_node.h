#ifndef __PWN_VARIABLE_DECL_NODE_H__
#define __PWN_VARIABLE_DECL_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>
#include <string>

namespace pwn {

  /**
   * Variable Node - Node represents variable declaration.
   */
  class variable_decl_node: public cdk::basic_node {
	 
	 // If its a declaration in a function arguments.
	bool _isFuncDecl;
	 
	// If the variable is private or not.
	bool _isLocal;
	
	// If the variable is imported from other module or not.
	bool _isImported;
	
	// If its a constant or not.
	bool _constant;
	
	cdk::expression_node *_init;
	
	std::string _id;
	
	std::string _name = "variable_decl_node";
	
	basic_type *_type;
	
	
  public:
    inline variable_decl_node(int lineno,bool funcDecl,bool isLocal,bool isImported,bool constant,basic_type* typ,std::string *id,cdk::expression_node* init) :
        cdk::basic_node(lineno),_isFuncDecl(funcDecl),_isLocal(isLocal),_isImported(isImported),_constant(constant),_init(init),_id(*id), _type(typ) {}
	
	
	inline bool isLocal(){
		return _isLocal;
	}
	
	inline bool isImported(){
		return _isImported;
	}
	
	inline bool isFuncDecl(){
		return _isFuncDecl;
	}
	
	inline bool constant(){
		return _constant;
	}
	
	inline cdk::expression_node* init(){
		return _init;
	}
	
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_decl_node(this, level);
    }

    inline std::string value(){ 
		return _id;
  }
    
     std::string name(){
      return _name;
    }
    
    basic_type *type(){
      return _type;
    }
  };

} // pwn

#endif
 
