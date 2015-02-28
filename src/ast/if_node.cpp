#include "if_node.hpp"

void IfNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- IfNode:" << std::endl;
	offsetcheck();
	_cond->print(out, offset + OFFS);
	_then->print(out, offset + OFFS);
	_els->print(out, offset + LOFFS, true);
}

std::shared_ptr<Value> IfNode::eval(const StackFrame & ctx) {
	std::shared_ptr<Value> val = _cond->eval(ctx);
	typecheck(
			std::vector<ValueType> {ValueType::BOOL},
			std::vector<ValueType> {val->type()});
	if (std::dynamic_pointer_cast<BoolValue>(_cond->eval(ctx))->nativeValue())
		return _then->eval(ctx);
	else
		return _els->eval(ctx);
}
