(defun fullength (x)
    (cond 
        ((null x) 0)
        ((atom x) 1)
        (t (+ (fullength (car x)) (fullength (cdr x))))
	)
)

(print (fullength `(1 2 3 4 5 3)))