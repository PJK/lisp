#include "lisp_exception.hpp"
#include "../value/value.hpp"
#include <vector>

#ifndef _TYPE_MISMATCH_EXCEPTION_HPP
#define _TYPE_MISMATCH_EXCEPTION_HPP

std::ostream & operator<<(std::ostream & out, const ValueType v);

std::ostream & operator<<(std::ostream & out, const std::vector<ValueType> vec);

class TypeMismatchException : public LispException {
	public:
		TypeMismatchException(std::vector<ValueType> expected, std::vector<ValueType> got) :
			_expected(expected), _got(got) { }
		
		virtual void explain(std::ostream & out);

	private:
		std::vector<ValueType> _expected, _got;
};
 
#endif