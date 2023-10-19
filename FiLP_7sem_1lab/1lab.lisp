(defun mean (lst)
  (/ (apply #'+ lst)
     (length lst))
)

(defun grade_point_average (x)
    (cond 
        ((null x) nil)
        (t 
            (GPA (car x))
            (grade_point_average (cdr x))
        )
    )
    
)

(defun get_list_evals (evals)
    (cond
        ((null evals) nil)
        (t
            (cons 
                (car (reverse (car evals))) 
                (get_list_evals (cdr evals))
            )
        )
    )
)

(defun GPA (x)
    (print 
        (cons (car x) (format nil "~,2f" (mean (get_list_evals (cdr x)))))
    )
)

(grade_point_average 
    `(
        ("studen1" ("mat" 4) ("prog" 4) ("inform" 3))
        ("studen2" ("mat" 5) ("prog" 4) ("inform" 5))
        ("studen3" ("mat" 3) ("prog" 4) ("inform" 4))
    )
)