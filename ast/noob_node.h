// $Id: noob_node.h,v 1.3 2015/04/12 12:51:07 ist176102 Exp $ -*- c++ -*-
#ifndef __PWN_NOOB_NODE_H__
#define __PWN_NOOB_NODE_H__


namespace pwn {

  /**
   * Class for describing noob node.
   */
  class noob_node: public cdk::expression_node {

  std::string _name = "noob_node";
  	  
  public:
    inline noob_node(int lineno) :
        cdk::expression_node(lineno) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_noob_node(this, level);
    }
  
  std::string name(){
      return _name;
    }
  };

} // pwn

#endif 
