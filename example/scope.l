(let x 5
	(let f (lambda (x) x)
		(f 1)))

(let y 5
	(let f (lambda (x) y)
		(f 1)))