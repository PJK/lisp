#include "value.hpp"
#include "../ast/formal_params_node.hpp"
#include "../ast/lambda_node.hpp"
#include "../stack_frame.hpp"


#ifndef _CLOSURE_VALUE_HPP
#define _CLOSURE_VALUE_HPP 

class ClosureValue : public Value {
	public:
		ClosureValue(LambdaNode * definition, const StackFrame & context) : _context(context) {
			_type = ValueType::CLOSURE;
			_definition = definition->preciseClone();
		};

		~ClosureValue() {
			delete _definition;
		}

		void print(std::ostream & out) {
			out << "Closure: " << std::endl;
			_definition->print(out, std::string(""));
			_context.print(out);
		}

		FormalParamsNode * formalParams() {
			return _definition->formalParams();
		}

		EvaluableNode * definition() {
			return _definition->body();
		}

		StackFrame context() {
			return _context;
		}
	private:
		LambdaNode * _definition;
		StackFrame _context;
};

#endif