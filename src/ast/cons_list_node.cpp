#include "cons_list_node.hpp"
#include "../value/list_nil_value.hpp"
#include "../value/list_value.hpp"

void ConsListNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- ConsListNode" << std::endl;
	offsetcheck();
	_head->print(out, offset + OFFS);
	_tail->print(out, offset + LOFFS, true);
}

std::shared_ptr<Value> ConsListNode::eval(const StackFrame & ctx) {
	return std::shared_ptr<ListValue>(new ListValue(_head->eval(ctx), _tail->eval(ctx)));
}