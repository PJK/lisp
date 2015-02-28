#include <iostream>
#include <map>
#include <memory>


#ifndef _VALUE_HPP
#define _VALUE_HPP 

class LambdaNode;

enum ValueType { INT, BOOL, LIST, CLOSURE };

class Value {
	public:
		virtual void print(std::ostream &) = 0;
		const ValueType type() { return _type; }
		virtual ~Value() {};
	protected:
		ValueType _type;
};

#endif 