#include "const_node.hpp"

#ifndef _NIL_LIST_NODE_HPP
#define _NIL_LIST_NODE_HPP
 
class NilListNode : public ConstNode {
	public:
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new NilListNode(*this);
		}
};
 
#endif