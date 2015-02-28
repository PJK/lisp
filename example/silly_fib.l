; The bad way - compare to parallel.l and fast_fib.l

(let silly-fib (lambda (n) 
	(if (<= n 2) 
		1 
		(+ (silly-fib (- n 1)) (silly-fib (- n 2)))))
	'((silly-fib 25) (silly-fib 25)))