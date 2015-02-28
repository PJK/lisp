#include <iostream>
#include "../ast/evaluable_node.hpp"
#include "../ast/params_node.hpp"
#include "../ast/formal_params_node.hpp"
#include "../../build/parser.hpp" //built by bison
#include "../stack_frame.hpp"
#include "../value/value.hpp"
#include "../exceptions/lisp_exception.hpp"

using namespace std;

extern int yyparse();
extern EvaluableNode * root;

int main(int argc, char **argv) {
    yyparse();
    StackFrame sf;
    sf.loadCorelib();
    //sf.print(cout);
    try {
    	root->eval(sf)->print(cout);
    } catch (LispException & e) {
    	e.explain(cout);
    }
    cout << endl;
    delete root;
    return 0;
}