#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/list_value.hpp"


#ifndef _LIST_CAR_HPP
#define _LIST_CAR_HPP
 
class ListCar : public BuiltinBody {
	public:
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new ListCar(*this);
		}
};
 
 
#endif