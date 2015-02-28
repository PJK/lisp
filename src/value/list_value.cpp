#include "list_value.hpp"

void ListValue::print(std::ostream & out) {
	if (isRealList())
		out << "List: '(";
	else
		out << "Pair: (";
	_car->print(out);
	out << ", ";
	_cdr->print(out);	
	out <<")";
} 