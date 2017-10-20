// $Id: symbol.h,v 1.8 2015/05/18 21:23:19 ist176046 Exp $ -*- c++ -*-
#ifndef __PWN_SEMANTICS_SYMBOL_H__
#define __PWN_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace pwn {

    class symbol {
		
		/* Symbol Type */
		basic_type *_type;
		
		/* Symbol Name */
		std::string _name;

	
		/*============================================0*/
	
		/* Used to indicate local variable offset. */
		int _addr;
		
		/* Used to indicate if symbol is local or global*/
		bool _islocal;
		
		/* Used to distinguish between function and variable.*/
		bool _isFunction;
		
		/* Used to know if a function is defined or not.*/
		bool _isDefined;
		
		public:
		inline symbol(basic_type *type, const std::string &name,
			int addr, bool islocal) :
			_type(type), _name(name),
			_addr(addr), _islocal(islocal) {
		}
		
		inline symbol(basic_type *type, const std::string &name,
			int addr, bool islocal,bool isFunction,bool isDefined) :
			_type(type), _name(name),
			_addr(addr), _islocal(islocal),_isFunction(isFunction),
			_isDefined(isDefined) {
		}
		
		virtual ~symbol() {
		}
		
		inline basic_type *type() const {
			return _type;
		}

		inline const std::string &name() const {
			return _name;
		}

		inline int addr() const {
			return _addr;
		}

		inline bool islocal() const{
			return _islocal;
		}
		
		inline bool isDefined() const{
			return _isDefined;
		}
		
		inline void isDefined(bool def){
			_isDefined = def;
		}
		
		inline bool isFunction() const{
			return _isFunction;
		}
    };

} // pwn

#endif
