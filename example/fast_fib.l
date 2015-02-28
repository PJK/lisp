(let cdar (lambda (lst) 
	(car (cdr lst)))
(let fib-acc (lambda (n acc) ; accumulator of previous numbers
	(if (>= n 1)
		(fib-acc (- n 1) (cons (+ (car acc) (cdar acc)) acc))
		(car acc)))
(let fib (lambda (n) 
	(fib-acc (- n 2) '(1 1)))
	
	(fib 25))))