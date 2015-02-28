#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/list_value.hpp"

 
#ifndef _LIST_CDR_HPP
#define _LIST_CDR_HPP
 
// Yeah, duplicate, but not worth http://stackoverflow.com/questions/4387971/c-passing-method-pointer-as-template-argument
class ListCdr : public BuiltinBody {
	public:
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new ListCdr(*this);
		}
};
 
 
#endif