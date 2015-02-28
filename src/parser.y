%{
    #include "../src/ast/if_node.hpp"
    #include "../src/ast/binding_node.hpp"
    #include "../src/ast/bool_node.hpp"
    #include "../src/ast/int_node.hpp"
    #include "../src/ast/params_node.hpp"
    #include "../src/ast/formal_params_node.hpp"
    #include "../src/ast/invocation_node.hpp"
    #include "../src/ast/lambda_node.hpp"
    #include "../src/ast/let_node.hpp"
    #include "../src/ast/nil_list_node.hpp"
    #include "../src/ast/cons_list_node.hpp"
    EvaluableNode * root;
    extern int yylex();
    extern int yylineno;
    extern char * yytext;
    void yyerror(const char *s) { 
      printf("ERROR: %s at line %d near %s\n", s, yylineno, yytext);
    }
%}

%union {
    EvaluableNode * node;
    ParamsNode * params;
    BindingNode * binding;
    FormalParamsNode * formal_parameters;
    std::string * string;
    int token;
}

%token <string> TIDENTIFIER TINTEGER
%token <token> TLPAREN TRPAREN TLET TLAMBDA TIF TTRUE TFALSE TNIL TQUOTE TTHUNK

%type<node> sexp literal if let lambda special_form quoted_list list thunk
%type<params> parameters 
%type<binding> binding
%type<formal_parameters> formal_parameters formal_parameters_list


%start root

%%
root: sexp { root = $1; }

sexp:       TLPAREN sexp parameters TRPAREN { $$ = new InvocationNode($2, $3); delete $2; delete $3; }
          | special_form
          | literal
          | binding { $$ = dynamic_cast<EvaluableNode *>($1); }
          ;   

special_form:   if
              | let
              | lambda
              | quoted_list
              | thunk
              ;

if:           TLPAREN TIF sexp sexp sexp TRPAREN { $$ = new IfNode($3, $4, $5); delete $3; delete $4; delete $5; }

let:          TLPAREN TLET binding sexp sexp TRPAREN { $$ = new LetNode($3, $4, $5); delete $3; delete $4; delete $5; }

lambda:       TLPAREN TLAMBDA formal_parameters sexp TRPAREN { $$ = new LambdaNode($3, $4); delete $3; delete $4; }

quoted_list:  TQUOTE TLPAREN list TRPAREN { $$ = $3; }

thunk:        TTHUNK sexp { auto tmp = new FormalParamsNode(); $$ = new LambdaNode(tmp, $2); delete $2; delete tmp; }

list:           /*empty*/     { $$ = new NilListNode(); }
              | sexp list     { $$ = new ConsListNode($1, $2); delete $1; delete $2; }
              ;

parameters:     /*empty*/         { $$ = new ParamsNode(); }
              | parameters sexp   { ($1)->push($2); $$ = $1; delete $2; }
              ;


formal_parameters:  TLPAREN formal_parameters_list TRPAREN { $$ = $2; }

formal_parameters_list:   /*empty*/                       { $$ = new FormalParamsNode(); }
                        | formal_parameters_list binding  { ($1)->push($2); $$ = $1; delete $2; }
                        ;

literal:    TINTEGER    { $$ = new IntNode($1); delete $1; }
          | TTRUE       { $$ = new BoolNode(true); }
          | TFALSE      { $$ = new BoolNode(false); }
          | TNIL        { $$ = new NilListNode(); }
          ;

binding:  TIDENTIFIER   { $$ = new BindingNode($1); delete $1; }


%%