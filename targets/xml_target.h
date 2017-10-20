// $Id: xml_target.h,v 1.1 2015/02/21 20:27:38 ist13500 Exp $
#ifndef __PWN_SEMANTICS_XML_EVALUATOR_H__
#define __PWN_SEMANTICS_XML_EVALUATOR_H__

#include <cdk/basic_target.h>
#include <cdk/compiler.h>
#include "targets/xml_writer.h"

namespace pwn {

  class xml_target: public cdk::basic_target {
    static xml_target _self;

  private:
    inline xml_target() :
        cdk::basic_target("xml") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      // this symbol table will be used to check identifiers
      // an exception will be thrown if identifiers are used before declaration
      cdk::symbol_table<pwn::symbol> symtab;

      xml_writer writer(compiler, symtab);
      compiler->ast()->accept(&writer, 0);
      return true;
    }

  };

} // pwn

#endif
