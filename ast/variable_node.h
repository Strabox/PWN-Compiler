#ifndef __PWN_VARIABLE_NODE_H__
#define __PWN_VARIABLE_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/expression_node.h>
#include <string>

namespace pwn {

  /**
   * Variable Node - Node represents variable (left value)
   */
  class variable_node: public pwn::lvalue_node {
	 
    std::string _id;  
	  
    std::string _name = "variable_node";
  
  public:
	inline variable_node(int lineno, std::string *id) :
		pwn::lvalue_node(lineno), _id(*id)  {}

	inline variable_node(int lineno) :
		pwn::lvalue_node(lineno) {}

	inline std::string value(){ 
		return _id;
	}

    

    
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

     std::string name(){
      return _name;
    }
    
  };

} // pwn

#endif
