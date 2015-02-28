#include "list_real.hpp"

std::shared_ptr<Value> ListReal::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	typecheck(
			std::vector<ValueType> {ValueType::LIST},
			std::vector<ValueType> {x1->type()});
	return std::shared_ptr<BoolValue>(new BoolValue(
		x1->type() == ValueType::LIST &&
		std::dynamic_pointer_cast<ListValue>(x1)->isRealList()));
}