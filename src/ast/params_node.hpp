#include "evaluable_node.hpp"
#include <vector>

#ifndef _PARAMS_NODE_HPP
#define _PARAMS_NODE_HPP

class ParamsNode : public Node {
	public:
		~ParamsNode();
		void push(EvaluableNode *);
		void print(std::ostream &, std::string, bool last = false);
		const std::vector<EvaluableNode *> values() { return _values; }
		ParamsNode * clone();
	private:
		std::vector<EvaluableNode *> _values;
};

#endif
