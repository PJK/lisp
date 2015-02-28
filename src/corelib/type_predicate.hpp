#include "builtin_body.hpp"
#include "corelib_macros.hpp"
#include "../value/bool_value.hpp"

#ifndef _TYPE_PREDICATE_HPP
#define _TYPE_PREDICATE_HPP
 
class TypePredicate : public BuiltinBody {
	public:
		TypePredicate(ValueType t) : _type(t) {}
		std::shared_ptr<Value> eval(const StackFrame &);
		EvaluableNode * clone() {
			return new TypePredicate(*this);
		}
	private:
		ValueType _type;
};
 
#endif
