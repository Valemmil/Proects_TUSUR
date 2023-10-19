; задание уравнения в виде списка
(setq meEquation '(A / x + B = C / x))

; выделение левой части относительно символа op
(defun left(e op)
    (if e
        (let ((f (first e)))
            (if (eq f op) nil
                (cons f (left (rest e) op))
            )
        )
        nil
     )
)

; выделение правой части относительно символа op
(defun right(e op)
    (if e
        (let ((r (rest e)))
            (if (eq (first e) op) r
                (right r op)
            )
        )
        nil
    )
)

; решение уравнения
(defun res(e)
    (let ((l (left e '=)))
        (if l
            (let(
                 (r (first (right e '=)))
                 (k (first (left l '+)))
                 (j (first (right l '+)))
                 (var (first (reverse (left l '+))))
                )
                (if (and r k var)
                    (list var '= "(" r '- k ")" '/ j)
                    nil
                )
            )
            nil
        )
    )
)

; вывод сообщения об ошибке при неправильно заданном уравнении
(defun res2(e)
    (let ((r (res e)))
        (if r r "Ошибка")
    )
)

; вывод результата решения
(princ (res2 meEquation))