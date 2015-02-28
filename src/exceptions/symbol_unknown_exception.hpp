#include "lisp_exception.hpp"

#ifndef _SYMBOL_UNKNOWN_EXCEPTION_HPP
#define _SYMBOL_UNKNOWN_EXCEPTION_HPP
 
class SymbolUnknownException : public LispException {
	public:
		SymbolUnknownException(std::string name) : 
			_name(name) {}
		virtual void explain(std::ostream & out) {
			out << "ERROR: symbol lookup failed: " << _name << std::endl;
		}
	private:
		std::string _name;
};
 
#endif