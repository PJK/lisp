#include <iostream>
#include <string>

#ifndef _NODE_HPP
#define _NODE_HPP

class Node {
	public: 
		virtual ~Node() {}
		virtual void print(std::ostream &, std::string, bool last = false) = 0;
};

#endif
