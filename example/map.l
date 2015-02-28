(let map (λ (list function)
  (if (nil? list)
      list
      (cons (function (car list)) (map (cdr list) function))))
  (map '(1 2 3 4 5) (λ (x) (* x x))))