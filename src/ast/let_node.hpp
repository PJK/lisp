#include "evaluable_node.hpp"
#include "binding_node.hpp"

#ifndef _LET_NODE_HPP
#define _LET_NODE_HPP

class LetNode : public EvaluableNode {
	public:
		LetNode(BindingNode * name, EvaluableNode * value, EvaluableNode * scope) {
			_name = name->preciseClone();
			_value = value->clone();
			_scope = scope->clone();
		}
		~LetNode() {
			delete _name;
			delete _value;
			delete _scope;
		}
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new LetNode(_name, _value, _scope);
		}
	private:
		BindingNode * _name;
		EvaluableNode * _value, * _scope;
};

#endif