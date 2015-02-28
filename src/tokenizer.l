%{
#include <string>
#include "../src/ast/evaluable_node.hpp"
#include "../src/ast/params_node.hpp"
#include "../src/ast/formal_params_node.hpp"
#include "parser.hpp"
#define SAVE_TOKEN {yylval.string = new std::string(yytext, yyleng); /* std::cout << *yylval.string << std::endl; */}
#define TOKEN(t) (yylval.token = t)
%}

%option noyywrap
%option yylineno

%%
";"[^\n]*
[ \t\n]            
"let"						            return TLET;
(λ|lambda)								return TLAMBDA;
"if"									return TIF;
"true"									return TTRUE;
"false"									return TFALSE;
"nil"									return TNIL;
[a-zA-Z_+-/*<>=%?]*					 	SAVE_TOKEN; return TIDENTIFIER;
[0-9]+                          		SAVE_TOKEN; return TINTEGER;
"("                             		return TLPAREN;
")"                             		return TRPAREN;
'										return TQUOTE;
~										return TTHUNK;
.                               		printf("Unknown token!\n"); yyterminate();

%%