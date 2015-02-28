#include <iostream>
#include <stdexcept>

#ifndef _LISP_EXCEPTION_HPP
#define _LISP_EXCEPTION_HPP
 
class LispException : public std::runtime_error {
	public:
		LispException() : std::runtime_error("LISP exception") {}
		LispException(std::string msg) : std::runtime_error("LISP exception: " + msg) {}
		virtual void explain(std::ostream & out) {
			out << "An error occured: " << what() << std::endl;
		}
};
 
#endif