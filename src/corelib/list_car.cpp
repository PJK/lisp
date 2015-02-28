#include "list_car.hpp"
#include "corelib_macros.hpp"

std::shared_ptr<Value> ListCar::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	typecheck(
			std::vector<ValueType> {ValueType::LIST},
			std::vector<ValueType> {x1->type()});
	return std::dynamic_pointer_cast<ListValue>(x1)->car();
}