#include "list_value.hpp"
#include "../exceptions/lisp_exception.hpp"

#ifndef _LIST_NIL_VALUE_HPP
#define _LIST_NIL_VALUE_HPP
 
class ListNilValue : public ListValue {
	public:
		ListNilValue() : ListValue(nullptr, nullptr) {}
		~ListNilValue() {}
		void print(std::ostream &); 
		bool isNil() { return true; }
		std::shared_ptr<Value> car() { throw LispException(); }
		std::shared_ptr<Value> cdr() { throw LispException(); }
		virtual bool isRealList() { return true; }
};
 
#endif
