#include <iostream>
#include "../ast/evaluable_node.hpp"
#include "../ast/params_node.hpp"
#include "../ast/formal_params_node.hpp"
#include "../../build/parser.hpp" //built by bison


using namespace std;

extern int yyparse();
extern Node * root;

int main(int argc, char **argv)
{
        yyparse();
        root->print(cout, string(""));
        delete root;
        return 0;
}