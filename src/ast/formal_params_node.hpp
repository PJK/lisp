#include "node.hpp"
#include <vector>
#include "binding_node.hpp"

#ifndef _FORMAL_PARAMS_NODE_HPP
#define _FORMAL_PARAMS_NODE_HPP

class BindingNode;

class FormalParamsNode : public Node {
	public:
		~FormalParamsNode();
		void push(BindingNode *);
		void print(std::ostream &, std::string, bool last = false);
		const std::vector<BindingNode *> names() const { return _names; }
		FormalParamsNode * clone();
	private:
		std::vector<BindingNode *> _names;
};

#endif
