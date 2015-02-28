#include "builtin_body.hpp"
#include "corelib_macros.hpp"

#ifndef _BINARY_INT_OP_HPP
#define _BINARY_INT_OP_HPP
 
class BinaryIntOp : public BuiltinBody {
	public:
		typedef int (*binop)(int, int);
		BinaryIntOp(binop f) : _func(f) {}
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new BinaryIntOp(*this);
		}
	private:
		binop _func;
};
 
#endif