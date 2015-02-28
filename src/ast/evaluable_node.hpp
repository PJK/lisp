#include "node.hpp"
#include <vector>
#include <memory>
#include "../value/value.hpp"
#include "../exceptions/type_mismatch_exception.hpp"

#ifndef _EVALUABLE_NODE_HPP
#define _EVALUABLE_NODE_HPP

class Value;
class StackFrame;

class EvaluableNode : public Node {
	public:
		virtual ~EvaluableNode() {}
		virtual EvaluableNode * clone() = 0;
		virtual std::shared_ptr<Value> eval(const StackFrame &) = 0; 
	protected:
		void typecheck(std::vector<ValueType> expected, std::vector<ValueType> got) {
			auto it = got.begin();
			for (auto & val : expected) {
				if (*it != val)
					throw TypeMismatchException(expected, got);
				++it;
			}
		}
};

#endif
