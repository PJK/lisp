#include "const_node.hpp"
#include "node_macros.cpp"


#ifndef _CONS_LIST_NODE_HPP
#define _CONS_LIST_NODE_HPP
 
class ConsListNode : public ConstNode {
	public:
		ConsListNode(EvaluableNode * head, EvaluableNode * tail) {
			_head = head->clone();
			_tail = tail->clone();
		}
		~ConsListNode() {
			delete _head;
			delete _tail;
		}
		void print(std::ostream &, std::string, bool last = false);
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new ConsListNode(_head, _tail);
		}
	private:
		EvaluableNode * _head, * _tail;
};
 
 
#endif