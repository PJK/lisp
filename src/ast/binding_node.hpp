#include "evaluable_node.hpp"

#ifndef _BINDING_NODE_HPP
#define _BINDING_NODE_HPP

class BindingNode : public EvaluableNode {
	public:
		BindingNode(std::string name) : _name(name) {};
		BindingNode(std::string * name) : _name(*name) {};
		void print(std::ostream &, std::string, bool last = false);
		std::string asString() { return _name; }
		~BindingNode() {}
		EvaluableNode * clone() {
			return new BindingNode(*this);
		}
		BindingNode * preciseClone() {
			return new BindingNode(*this);
		}
		std::shared_ptr<Value> eval(const StackFrame &); 
	private:
		std::string _name;
};

#endif
