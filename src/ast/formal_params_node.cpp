#include "formal_params_node.hpp"
#include "node_macros.cpp"

FormalParamsNode::~FormalParamsNode() {
	for (auto & param : _names)
		delete param;
}

FormalParamsNode * FormalParamsNode::clone() {
	auto res = new FormalParamsNode();
	for (auto & param : _names)
		res->push(param);
	return res;
}

void FormalParamsNode::push(BindingNode * ref) {
	_names.push_back(ref->preciseClone());
}

void FormalParamsNode::print(std::ostream & out, std::string offset, bool last) {
	out << offset << "-- FormalParamsNode:" << std::endl;
	offsetcheck();
	// Use EOFFS for the last member
	for (int i = 0; i < _names.size(); i++)
		if (i != _names.size() - 1)
			_names[i]->print(out, offset + OFFS);
		else
			_names[i]->print(out, offset + LOFFS, true);
}