#include <map>
#include <string>
#include <set>
#include "ast/formal_params_node.hpp"
#include "ast/params_node.hpp"
#include "ast/lambda_node.hpp"
#include "corelib/builtin_params.hpp"

#ifndef _STACK_FRAME_HPP
#define _STACK_FRAME_HPP 

class StackFrame {
	public:
		typedef int (*binop)(int, int);
		typedef bool (*bincmp)(int, int);
		/**
		 * Substitute formal parameters into this context
		 */
		void substitute(const FormalParamsNode *, ParamsNode *);
		void insert(std::string, std::shared_ptr<Value>, bool core = false);
		void print(std::ostream &);
		void merge(const StackFrame & other);
		std::shared_ptr<Value> lookup(const std::string &) const;
		void loadCorelib();
	private:
		std::map<std::string, std::shared_ptr<Value>> _data;
		std::set<std::string> _core;

		void insertBinOp(binop op, const std::string & name, StackFrame & ctx);
		void insertBinComp(bincmp op, const std::string & name, StackFrame & ctx);
		void insertTypePred(ValueType vt, const std::string & name, StackFrame & ctx);
		
		template<typename T>
		void insertUnary(const std::string & name, StackFrame & ctx) {
			auto params = new BuiltinParams1();	
			auto pred = new T;
			auto lambda = new LambdaNode(params, pred);	
			insert(name, lambda->eval(ctx), true);	
			delete params;
			delete pred; 
			delete lambda;
		}
};

#endif