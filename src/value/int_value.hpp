#include "value.hpp"

#ifndef _INT_VALUE_HPP
#define _INT_VALUE_HPP 

class IntValue : public Value {
	public:
		IntValue(int val) : _val(val) {
			_type = ValueType::INT;
		};
		int nativeValue() { return _val; };
		void print(std::ostream & out) {
			out << "Integer: " << nativeValue();
		} 
	private:
		int _val;
};

#endif