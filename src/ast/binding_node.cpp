#include "binding_node.hpp"
#include "../stack_frame.hpp"


void BindingNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- BindingNode: name='" << _name  << "'" << std::endl;
}

std::shared_ptr<Value> BindingNode::eval(const StackFrame & ctx) {
	return ctx.lookup(this->asString());
}