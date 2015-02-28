#include "int_node.hpp"
#include "../value/int_value.hpp"
#include <sstream>

IntNode::IntNode(std::string * data) {
	std::istringstream(*data) >> _value;
}

std::shared_ptr<Value> IntNode::eval(const StackFrame &) {
	return std::shared_ptr<IntValue>(new IntValue(_value));
}

void IntNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- IntNode: " << _value << std::endl;
}