#include "../ast/formal_params_node.hpp"
#include "corelib_macros.hpp"

#ifndef _BUILTIN_PARAMS_HPP
#define _BUILTIN_PARAMS_HPP 

class BuiltinParams1 : public FormalParamsNode {
	public:
		BuiltinParams1() {
			auto x1 = new BindingNode(CORELIB_X1);
			push(x1);
			delete x1;
		}
};
 
class BuiltinParams2 : public FormalParamsNode {
	public:
		BuiltinParams2() {
			auto x1 = new BindingNode(CORELIB_X1);
			auto x2 = new BindingNode(CORELIB_X2);
			push(x1);
			push(x2);
			delete x1; delete x2;
		}
};


#endif