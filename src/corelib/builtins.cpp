#include "builtins.hpp"
#define BININT(name, op) int Builtins::name(int a, int b) { return a op b; }
#define BININTCMP(name, op) bool Builtins::name(int a, int b) { return a op b; }



BININT(plus, +)
BININT(minus, -)
BININT(mult, *)
BININT(div, /)
BININT(mod, %)
BININTCMP(eq, ==)
BININTCMP(lt, <)
BININTCMP(gt, >)
BININTCMP(leq, <=)
BININTCMP(geq, >=)