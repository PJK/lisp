#include "const_node.hpp"

#ifndef _INT_NODE_HPP
#define _INT_NODE_HPP

class IntNode : public ConstNode {
	public:
		IntNode(std::string *);
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new IntNode(*this);
		}
	private:
		int _value;
};

#endif