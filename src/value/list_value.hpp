#include "value.hpp"

#ifndef _LIST_VALUE_HPP
#define _LIST_VALUE_HPP 

class ListValue : public Value {
	public:
		ListValue(std::shared_ptr<Value> car, std::shared_ptr<Value> cdr) : _car(car), _cdr(cdr) {
			_type = ValueType::LIST;
		};
		virtual std::shared_ptr<Value> car() { return _car; }
		virtual std::shared_ptr<Value> cdr() { return _cdr; }
		virtual void print(std::ostream &); 
		virtual bool isNil() { return false; }
		/**
		Is this "list" a list by the recursive definition?
		*/
		virtual bool isRealList() { 
			return (_cdr->type() == ValueType::LIST) && std::dynamic_pointer_cast<ListValue>(_cdr)->isRealList(); 
		}
	private:
		std::shared_ptr<Value> _car;
		std::shared_ptr<Value> _cdr;
};

#endif