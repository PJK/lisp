#include "value.hpp"

#ifndef _BOOL_VALUE_HPP
#define _BOOL_VALUE_HPP 

class BoolValue : public Value {
	public:
		BoolValue(bool val) : _val(val) {
			_type = ValueType::BOOL;
		};
		bool nativeValue() { return _val; };
		void print(std::ostream & out) {
			out << "Boolean: " << (_val ? "true" : "false");
		}
	private:
		bool _val;
};

#endif
