#include "evaluable_node.hpp"
#include "../value/bool_value.hpp"
#include "node_macros.cpp"

#ifndef _IF_NODE_HPP
#define _IF_NODE_HPP

class IfNode : public EvaluableNode {
	public:
		IfNode(EvaluableNode * cond, EvaluableNode * then, EvaluableNode * els) {
			_cond = cond->clone();
			_then = then->clone();
			_els = els->clone();
		}
		~IfNode() {
			delete _cond;
			delete _then;
			delete _els;
		}
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new IfNode(_cond, _then, _els);
		}
	private:
		EvaluableNode * _cond, * _then, * _els;
};

#endif