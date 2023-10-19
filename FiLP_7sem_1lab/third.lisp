(defun copy (x n)
    (cond
        ((> n 0) 
            (cons (list x) (copy x (- n 1)))
        )
    )
)

(print (copy 1 3))