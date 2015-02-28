#include "stack_frame.hpp"
#include <iostream>
#include "ast/lambda_node.hpp"
#include "corelib/binary_int_op.hpp"
#include "corelib/binary_int_comp.hpp"
#include "corelib/builtins.hpp"
#include "corelib/list_nil.hpp"
#include "corelib/list_cons.hpp"
#include "corelib/list_real.hpp"
#include "corelib/list_car.hpp"
#include "corelib/list_cdr.hpp"
#include "corelib/type_predicate.hpp"
#include "corelib/list_parallel.hpp"
#include "exceptions/arity_mismatch_exception.hpp"
#include "exceptions/symbol_unknown_exception.hpp"

using namespace std;

void StackFrame::substitute(FormalParamsNode const * formal, ParamsNode * actual) {
	auto act = actual->values();
	int i = 0;
	if (act.size() != formal->names().size())
		throw ArityMismatchException(formal->names().size(), act.size());
	for (auto frm : formal->names()) {
		insert(frm->asString(), act.at(i++)->eval(*this));
	}
}

void StackFrame::merge(const StackFrame & other) {
	for (auto & it : other._data) {
		_data.insert(it);
	}	
}

void StackFrame::insert(std::string key, std::shared_ptr<Value> val, bool core) {
	if (core)
		_core.insert(key);
	auto cp = _data.find(key);
	if (cp != _data.end()) {
		_data.erase(cp);
	}
	_data.insert(std::make_pair(key, val));
}

void StackFrame::print(std::ostream & out) {
	out << "StackFrame bindings:" << endl;
	for(auto it = _data.cbegin(); it != _data.cend(); it++) {
		if (_core.find(it->first) == _core.end()) {
			out << it->first << " ";
			it->second->print(out);
			out << endl;
		}
	}
}

std::shared_ptr<Value> StackFrame::lookup(const std::string & key) const {
	try {
		return _data.at(key);
	} catch (std::out_of_range & e) {
		throw SymbolUnknownException(key);
	}
}


void StackFrame::insertBinOp(binop op, const std::string & name, StackFrame & ctx) {
	auto params = new BuiltinParams2();	
	auto bop = new BinaryIntOp(op);
	insert(name, LambdaNode(params, bop).eval(ctx), true);	
	delete params;
	delete bop; 
}

void StackFrame::insertBinComp(bincmp op, const std::string & name, StackFrame & ctx) {
	auto params = new BuiltinParams2();	
	auto bop = new BinaryIntComp(op);
	insert(name, LambdaNode(params, bop).eval(ctx), true);	
	delete params;
	delete bop; 
}

void StackFrame::insertTypePred(ValueType vt, const std::string & name, StackFrame & ctx) {
	auto params = new BuiltinParams1();	
	auto tp = new TypePredicate(vt);
	insert(name, LambdaNode(params, tp).eval(ctx), true);	
	delete params;
	delete tp;
}


#define UNARY(name) (new LambdaNode(new BuiltinParams1(), new name()))->eval(ctx)


void StackFrame::loadCorelib() {
	StackFrame ctx;
	insertBinOp(&Builtins::plus, "+", ctx);
	insertBinOp(&Builtins::minus, "-", ctx);
	insertBinOp(&Builtins::div, "/", ctx);
	insertBinOp(&Builtins::mod, "%", ctx);
	insertBinOp(&Builtins::mult, "*", ctx);
	insertBinComp(&Builtins::eq, "=", ctx);
	insertBinComp(&Builtins::lt, "<", ctx);
	insertBinComp(&Builtins::gt, ">", ctx);
	insertBinComp(&Builtins::leq, "<=", ctx);
	insertBinComp(&Builtins::geq, ">=", ctx);
	insertTypePred(ValueType::INT, "int?", ctx);
	insertTypePred(ValueType::LIST, "pair?", ctx);
	insertTypePred(ValueType::BOOL, "bool?", ctx);
	insertTypePred(ValueType::CLOSURE, "closure?", ctx);
	// a list is-a pair, but not necessarily the other way around
	insertUnary<ListNil>("nil?", ctx);
	insertUnary<ListReal>("list?", ctx);
	insertUnary<ListCar>("car", ctx);
	insertUnary<ListCdr>("cdr", ctx);
	insertUnary<ListParallel>("parallel", ctx);
	
	auto params = new BuiltinParams2();	
	auto tp = new ListCons();
	insert("cons", LambdaNode(params, tp).eval(ctx), true);
	delete params;
	delete tp; 
}