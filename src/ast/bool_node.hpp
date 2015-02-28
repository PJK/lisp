#include "const_node.hpp"

#ifndef _BOOL_NODE_HPP
#define _BOOL_NODE_HPP

class BoolNode : public ConstNode {
	public:
		BoolNode(bool val) : _value(val) {}
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new BoolNode(*this);
		}
	private:
		bool _value;
};

#endif