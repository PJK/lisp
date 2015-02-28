#include "params_node.hpp"
#include "node_macros.cpp"

void ParamsNode::push(EvaluableNode * ref) {
	_values.push_back(ref->clone());
}

void ParamsNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- ParamsNode:" << std::endl;
	offsetcheck();
	// Use EOFFS for the last member
	for (int i = 0; i < _values.size(); i++)
		if (i != _values.size() - 1)
			_values[i]->print(out, offset + OFFS);
		else
			_values[i]->print(out, offset + LOFFS, true);
}

ParamsNode * ParamsNode::clone() {
	auto res = new ParamsNode();
	for (auto & param : _values)
		res->push(param);
	return res;
}

ParamsNode::~ParamsNode() {
	for (auto & param : _values)
		delete param;
}