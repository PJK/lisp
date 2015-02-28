#include "evaluable_node.hpp"
#include "params_node.hpp"

#ifndef _INVOCATION_NODE_HPP
#define _INVOCATION_NODE_HPP

class InvocationNode : public EvaluableNode {
	public:
		~InvocationNode();
		InvocationNode(Node * target, ParamsNode * params) {
			_params = params->clone();
			_target = dynamic_cast<EvaluableNode *>(target)->clone();
		};
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone();
	private:
		EvaluableNode * _target;
		ParamsNode * _params;
}; 

#endif