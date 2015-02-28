; The bad way - compare to silly_fib.l and fast_fib.l
(let fib (λ (n)
	(if (<= n 2) 
		1 
		(+ (fib (- n 1)) (fib (- n 2)))))
	(parallel '(~(fib 25) ~(fib 25)) ))