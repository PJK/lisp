#include "list_nil.hpp"

std::shared_ptr<Value> ListNil::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	typecheck(
			std::vector<ValueType> {ValueType::LIST},
			std::vector<ValueType> {x1->type()});
	return std::shared_ptr<BoolValue>(new BoolValue(std::dynamic_pointer_cast<ListValue>(x1)->isNil()));
}