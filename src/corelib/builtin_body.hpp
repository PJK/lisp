#include "../ast/evaluable_node.hpp"
#include "../value/int_value.hpp"
#include "../exceptions/type_mismatch_exception.hpp"
#include "../stack_frame.hpp"


#ifndef _BUILTIN_BODY_HPP
#define _BUILTIN_BODY_HPP
 

class BuiltinBody : public EvaluableNode {
	public:
		void print(std::ostream & out, std::string offset, bool last = false) {
			out << offset << "-- <corelib native function>" << std::endl;
		}
};
 
#endif