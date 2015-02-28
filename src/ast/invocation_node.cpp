#include "invocation_node.hpp"
#include "../value/closure_value.hpp"
#include "node_macros.cpp"

InvocationNode::~InvocationNode() {
	delete _target;
	delete _params;
}

void InvocationNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- InvocationNode:" << std::endl;
	offsetcheck();
	_target->print(out, offset + OFFS);
	_params->print(out, offset + LOFFS, true);
}

EvaluableNode * InvocationNode::clone() {
	return new InvocationNode(_target, _params);
}

std::shared_ptr<Value> InvocationNode::eval(const StackFrame & context) {
	// Assume that the target is a closure
	std::shared_ptr<ClosureValue> target = std::dynamic_pointer_cast<ClosureValue>(_target->eval(context));
	//TODO
	if (target == nullptr) throw LispException("Invoking a non-callable value");
	// Evaluate the body of the closure, substituting formal parameters in the context
	StackFrame local_ctx(context);
	local_ctx.merge(target->context());
	local_ctx.substitute(target->formalParams(), _params);
	return target->definition()->eval(local_ctx);
}