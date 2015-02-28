#include "let_node.hpp"
#include "node_macros.cpp"
#include "../stack_frame.hpp"


void LetNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- LetNode:" << std::endl;
	offsetcheck();
	_name->print(out, offset + OFFS);
	_value->print(out, offset + OFFS);
	_scope->print(out, offset + LOFFS, true);
}

std::shared_ptr<Value> LetNode::eval(const StackFrame & ctx) {
	StackFrame new_ctx(ctx);
	new_ctx.insert(_name->asString(), _value->eval(ctx));
	return _scope->eval(new_ctx);
}
