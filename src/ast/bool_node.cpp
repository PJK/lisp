#include "bool_node.hpp"
#include "../value/bool_value.hpp"

std::shared_ptr<Value> BoolNode::eval(const StackFrame &) {
	return std::shared_ptr<BoolValue>(new BoolValue(_value));
}

void BoolNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- BoolNode: " << (_value ? "true" : "false") << std::endl;
}