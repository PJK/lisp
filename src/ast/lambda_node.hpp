#include "evaluable_node.hpp"
#include "formal_params_node.hpp"

#ifndef _LAMBDA_NODE_HPP
#define _LAMBDA_NODE_HPP

class LambdaNode : public EvaluableNode {
	public:
		LambdaNode(FormalParamsNode * params, EvaluableNode * body);
		~LambdaNode();
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &); 
		FormalParamsNode * formalParams() { return _params; }
		EvaluableNode * body() { return _body; }
		EvaluableNode * clone();
		LambdaNode * preciseClone();
	private:
		FormalParamsNode * _params;
		EvaluableNode * _body;
};

#endif
