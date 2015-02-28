#include "nil_list_node.hpp"
#include "../value/list_nil_value.hpp"

void NilListNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- NilListNode" << std::endl;
}

std::shared_ptr<Value> NilListNode::eval(const StackFrame &) {
	return std::shared_ptr<ListNilValue>(new ListNilValue());
}