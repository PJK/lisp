#include "builtin_body.hpp"
#include <thread>
#include "corelib_macros.hpp"
#include "../value/list_value.hpp"
#include "../value/list_nil_value.hpp"
#include "../value/closure_value.hpp"
#include "../exceptions/lisp_exception.hpp"

#ifndef _LIST_PARALLEL_HPP
#define _LIST_PARALLEL_HPP
 
class ListParallel : public BuiltinBody {
	public:
		std::shared_ptr<Value> eval(const StackFrame & ctx);
		EvaluableNode * clone() {
			return new ListParallel(*this);
		}
	private:
		std::vector<std::shared_ptr<ClosureValue>> collect(std::shared_ptr<ListValue> lst);
		std::shared_ptr<ListValue> buildList(std::shared_ptr<ListValue> prev, std::vector<std::shared_ptr<Value>> & vals);
};
 
#endif