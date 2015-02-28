#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/bool_value.hpp"
#include "../value/list_value.hpp"

 
#ifndef _LIST_NIL_HPP
#define _LIST_NIL_HPP
 
class ListNil : public BuiltinBody {
	public:
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new ListNil(*this);
		}
};
 

 
#endif