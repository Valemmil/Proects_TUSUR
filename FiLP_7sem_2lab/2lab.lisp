(defun eq0 (n)
    (> n 0)
)

(defun filter (p x)
    (cond
        ((atom x) ())
        ((funcall p (car x)) 
            (cons (car x) 
                (filter p (cdr x)))
        )
        (t (filter p (cdr x)))
    )
)

(print (filter `eq0 '(1 0 1 2 0 4 3 5 6)))