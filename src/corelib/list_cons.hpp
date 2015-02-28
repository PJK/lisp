#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/list_value.hpp"

#ifndef _LIST_CONS_HPP
#define _LIST_CONS_HPP
 
class ListCons : public BuiltinBody {
	public:
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new ListCons(*this);
		}
};
 
#endif