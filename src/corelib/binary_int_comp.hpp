#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/int_value.hpp"
#include "../value/bool_value.hpp"

#ifndef _BINARY_INT_COMP_HPP
#define _BINARY_INT_COMP_HPP
 
class BinaryIntComp : public BuiltinBody {
	public:
		typedef bool (*binop)(int, int);
		BinaryIntComp(binop f) : _func(f) {}
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new BinaryIntComp(*this);
		}
	private:
		binop _func;
};

#endif