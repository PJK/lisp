#include "binary_int_op.hpp"
#include "corelib_macros.hpp"

std::shared_ptr<Value> BinaryIntOp::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	auto x2 = ctx.lookup(CORELIB_X2);
	typecheck(
			std::vector<ValueType> {ValueType::INT, ValueType::INT},
			std::vector<ValueType> {x1->type(), x2->type()});
	return std::shared_ptr<IntValue>(new IntValue(
		(*_func)(std::dynamic_pointer_cast<IntValue>(x1)->nativeValue(),
				 std::dynamic_pointer_cast<IntValue>(x2)->nativeValue())));
}