(defun factor (a)
    (* a (factor (- a 1)))
)

(print (factor 7))