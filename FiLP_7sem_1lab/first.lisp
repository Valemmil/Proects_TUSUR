(defun prelast (array)
    (car 
        (cdr
            (reverse array)
        )   
    )
)

(print (prelast `(1 2 3 4 5)))