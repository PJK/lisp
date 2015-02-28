#include "type_mismatch_exception.hpp"

std::ostream & operator<<(std::ostream & out, const ValueType v) {
	switch (v) {
		case ValueType::INT: 
			out << "INT"; break;
		case ValueType::BOOL: 
			out << "BOOL"; break;
		case ValueType::LIST: 
			out << "LIST"; break;
		case ValueType::CLOSURE: 
			out << "CLOSURE"; break;
	}
	return out;
}

std::ostream & operator<<(std::ostream & out, const std::vector<ValueType> vec) {
	for (auto it = vec.begin(); it != vec.end(); it++) {
		out << *it;
		if (it != vec.end() - 1)
			out << ", ";
	}
	return out;
}

void TypeMismatchException::explain(std::ostream & out) {
	out << "ERROR: Type mismatch" << std::endl;
	out << "Expected: " << _expected << std::endl;
	out << "Got: " << _got << std::endl;

}