#include "type_predicate.hpp"

std::shared_ptr<Value> TypePredicate::eval(const StackFrame & ctx) {
	return std::shared_ptr<BoolValue>(new BoolValue(
		ctx.lookup(CORELIB_X1)->type() == _type
	));
}