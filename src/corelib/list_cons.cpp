#include "list_cons.hpp"

std::shared_ptr<Value> ListCons::eval(const StackFrame & ctx) {
	auto x1 = ctx.lookup(CORELIB_X1);
	auto x2 = ctx.lookup(CORELIB_X2);
	return std::make_shared<ListValue>(x1, x2);
}