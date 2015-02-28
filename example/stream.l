(let take (λ (k stream) 
	(if (= k 0)
		nil
		(cons (car stream) (take (- k 1) ((cdr stream))))))
(let nats (λ (n)
		(cons n ~(nats (+ 1 n))))
	(take 3 (nats 5))))