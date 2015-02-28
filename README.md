## Building
Requirements:
- C++11 compatible compiler (tested with g++ 4.8.1 and clang++ 3.4)
- flex (tested with 2.5.35)
- reasonably modern version of bison (tested with 2.7.12-4996)
- POSIX threading libraries (pthread)
- make
- doxygen (only if you want the generated documentation)

~~~~~~~~~~~~~~~~~~~~~
CPPFLAGS+=-O3 make -j 8 all
~~~~~~~~~~~~~~~~~~~~~

Binaries will be in `build/bin`; for Doxygen docs, check `docs/html`

If you want to build using clang++ & libc++, just make sure you have a libc++ compatible version of clang, and do
~~~~~~~~~~~~~~~~~~~~~
CPPFLAGS+='-stdlib=libc++ -O3' CXX=clang++-libc++ make -B -j 8 all
~~~~~~~~~~~~~~~~~~~~~

## Usage

There are two binaries: `simple_parser` and `interpreter`. Both accept data from the standard input.

Example:

~~~~~~~~~~~~~~~~~~~~~
pjk@deepThought2 ~/mff/lisp2$ echo "((lambda (x y z) (+ (+ x y) z)) 1 3 5)" | build/bin/interpreter
Integer: 9

pjk@deepThought2 ~/mff/lisp2$ echo "((lambda (x y z) (+ (+ x y) z)) 1 3 5)" | build/bin/simple_parser 
-- InvocationNode:
   |-- LambdaNode:
   |   |-- FormalParamsNode:
   |   |   |-- BindingNode: name='x'
   |   |   |-- BindingNode: name='y'
   |   |   \-- BindingNode: name='z'
   |   \-- InvocationNode:
   |       |-- BindingNode: name='+'
   |       \-- ParamsNode:
   |           |-- InvocationNode:
   |           |   |-- BindingNode: name='+'
   |           |   \-- ParamsNode:
   |           |       |-- BindingNode: name='x'
   |           |       \-- BindingNode: name='y'
   |           \-- BindingNode: name='z'
   \-- ParamsNode:
       |-- IntNode: 1
       |-- IntNode: 3
       \-- IntNode: 5

~~~~~~~~~~~~~~~~~~~~~

## Special forms

For more examples, see the `example` directory and

### `let`

Create a named value

~~~~~~~~~~~~~~~~~~~~~
(let name value scope)
~~~~~~~~~~~~~~~~~~~~~

### Examples
~~~~~~~~~~~~~~~~~~~~~
(let x 42
  x) ; 42

(let square (lambda (x) (* x x))
  (square 5)) ; 25
~~~~~~~~~~~~~~~~~~~~~

### `if`

Simple conditional

~~~~~~~~~~~~~~~~~~~~~
(if cond then else)
~~~~~~~~~~~~~~~~~~~~~

#### Examples

~~~~~~~~~~~~~~~~~~~~~
(let fact (lambda (n) 
	(if (<= n 1) 
	    n 
	    (* n (fact (- n 1))))) 
	(fact 6)) ; 720
~~~~~~~~~~~~~~~~~~~~~

### `lambda`

An anonymous function

~~~~~~~~~~~~~~~~~~~~~
(lambda params body)
~~~~~~~~~~~~~~~~~~~~~

#### Examples

~~~~~~~~~~~~~~~~~~~~~
((lambda (x y z) (+ (+ x y) z)) 1 3 5) ; 9
~~~~~~~~~~~~~~~~~~~~~

### `parallel`

Takes a list of thunks (nullary closures) and evaluates them all in parallel 

~~~~~~~~~~~~~~~~~~~~~
(parallel vector-of-thunks)
~~~~~~~~~~~~~~~~~~~~~

#### Examples
~~~~~~~~~~~~~~~~~~~~~
(let fib (λ (n) ; silly way to compute n-t Fibonacci's number
	(if (<= n 2) 
		1 
		(+ (fib (- n 1)) (fib (- n 2)))))
	(parallel '(~(fib 25) ~(fib 25)) )) ; should take about the same time as computing (fib 25) on a multicore machine - see examples/parallel.l
~~~~~~~~~~~~~~~~~~~~~

## Syntactical features

- `lambda` is equivalent to `λ`
- anything from `;` to the end of the line is a comment
- repeated whitespace is insignificant
- all identifiers are case sensitive

### Shortcut for delayed computations - `~`
Takes any S-expression and creates a thunk from it (effectively wraps it in a nullary lambda) 

~~~~~~~~~~~~~~~~~~~~~
~s-exp
~~~~~~~~~~~~~~~~~~~~~

### Examples
~~~~~~~~~~~~~~~~~~~~~
~5
; Closure: 
; -- LambdaNode:
;    |-- FormalParamsNode:
;    \-- IntNode: 5
; StackFrame bindings:
(~5) ; 5
~~~~~~~~~~~~~~~~~~~~~

Lazy generative streams:
~~~~~~~~~~~~~~~~~~~~~
(let take (λ (k stream) ; take k items from a stream
	(if (= k 0)
		nil
		(cons (car stream) (take (- k 1) ((cdr stream))))))
(let nats (λ (n) ; stream of integers starting from n
		(cons n ~(nats (+ 1 n))))
	(take 3 (nats 5)))) ; '(5 6 7)
~~~~~~~~~~~~~~~~~~~~~

### '() lists

~~~~~~~~~~~~~~~~~~~~~
'([s-exp1[ s-exp2[ ...]])
~~~~~~~~~~~~~~~~~~~~~

Examples

~~~~~~~~~~~~~~~~~~~~~
(let map (λ (list function)
  (if (nil? list)
      list
      (cons (function (car list)) (map (cdr list) function))))
  (map '(1 2 3 4 5) (λ (x) (* x x)))) ; '(1 4 9 16 25)
~~~~~~~~~~~~~~~~~~~~~

## Built-in functions & constants

~~~~~~~~~~~~~~~~~~~~~
Integers, int?
<, >, =, <=, =>
+, -, *, /, %
true, false - bool literals, bool?
nil - the empty list
cons, car, cdr, nil?, list?, pair?
cons has 'pair' semantics to allow for lazy streams
~~~~~~~~~~~~~~~~~~~~~

It is worth noting that all the builtins are first-class values, just like any other function, so we can do
~~~~~~~~~~~~~~~~~~~~~
(let apply (lambda (a b op) (op a b))
	(apply 1 1 +)) ;2
~~~~~~~~~~~~~~~~~~~~~
or even
~~~~~~~~~~~~~~~~~~~~~
+
~~~~~~~~~~~~~~~~~~~~~
which will give you something like 
~~~~~~~~~~~~~~~~~~~~~
Closure: 
-- LambdaNode:
   |-- FormalParamsNode:
   |   |-- BindingNode: name='__intrinsic_x1'
   |   \-- BindingNode: name='__intrinsic_x2'
   \-- <corelib native function>
StackFrame bindings:
~~~~~~~~~~~~~~~~~~~~~

You can even do evil things such as
~~~~~~~~~~~~~~~~~~~~~
(let + (lambda (a b) (- a b))
  (+ 3 5)) ; -2
~~~~~~~~~~~~~~~~~~~~~