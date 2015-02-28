#include "binary_int_comp.hpp"

std::shared_ptr<Value> BinaryIntComp::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	auto x2 = ctx.lookup(CORELIB_X2);
	try {
		typecheck(
				std::vector<ValueType> {ValueType::INT, ValueType::INT},
				std::vector<ValueType> {x1->type(), x2->type()});
	} catch (TypeMismatchException e) {
		if (x1->type() == ValueType::BOOL && x2->type() == ValueType::BOOL) {
			return std::shared_ptr<BoolValue>(new BoolValue(
					(bool)((*_func)	((int)std::dynamic_pointer_cast<BoolValue>(x1)->nativeValue(),
				 					 (int)std::dynamic_pointer_cast<BoolValue>(x2)->nativeValue()))));
		} else {
			throw e;
		}
	}
	return std::shared_ptr<BoolValue>(new BoolValue(
		(*_func)(std::dynamic_pointer_cast<IntValue>(x1)->nativeValue(),
				 std::dynamic_pointer_cast<IntValue>(x2)->nativeValue())));
}