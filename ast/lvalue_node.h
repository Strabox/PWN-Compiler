// $Id: lvalue_node.h,v 1.5 2015/05/16 13:22:45 ist176102 Exp $
#ifndef __PWN_NODE_EXPRESSION_LEFTVALUE_H__
#define __PWN_NODE_EXPRESSION_LEFTVALUE_H__

#include <cdk/ast/expression_node.h>
#include <string>

namespace pwn {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_node: public cdk::expression_node {
  	  
  std::string _name = "lvalue_node";
    
  public:
    inline lvalue_node(int lineno) :
        cdk::expression_node(lineno)  {}
        
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */

    
  std::string name(){
      return _name;
    }
    
  };

} // pwn

#endif
