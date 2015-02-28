#include "lambda_node.hpp"
#include "node_macros.cpp"
#include "../value/closure_value.hpp"

LambdaNode::LambdaNode(FormalParamsNode * params, EvaluableNode * body) {
	_params = params->clone();
	_body = body->clone();
}

EvaluableNode * LambdaNode::clone() {
	return new LambdaNode(_params, _body);
}

LambdaNode * LambdaNode::preciseClone() {
	return new LambdaNode(_params, _body);
}

LambdaNode::~LambdaNode() {
	delete _params;
	delete _body;
}

void LambdaNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- LambdaNode:" << std::endl;
	offsetcheck();
	_params->print(out, offset + OFFS);
	_body->print(out, offset + LOFFS, true);
}

std::shared_ptr<Value> LambdaNode::eval(const StackFrame & context) {
	return std::shared_ptr<ClosureValue>(new ClosureValue(this, context));
}
