доска(8).

шаги_коня(1, 2).
шаги_коня(2, 1).
шаги_коня(1, -2).
шаги_коня(2, -1).
шаги_коня(-1, 2).
шаги_коня(-2, 1).
шаги_коня(-1, -2).
шаги_коня(-2, -1).


позиция_валидна(PosX, PosY) :-
	доска(Размер),
	PosX >= 1, PosX =< Размер,
	PosY >= 1, PosY =< Размер.

генерация_позиций_коня(StartX, StartY, 0, _, []) :-
    позиция_валидна(StartX, StartY).

генерация_позиций_коня(StartX, StartY, N, Visited, [EndX-EndY | Positions]) :-
    N > 0,
    шаги_коня(DeltaX, DeltaY),
    EndX is StartX + DeltaX,
    EndY is StartY + DeltaY,
    позиция_валидна(EndX, EndY),
    \+ member(EndX-EndY, Visited),
    N1 is N - 1,
    генерация_позиций_коня(EndX, EndY, N1, [EndX-EndY | Visited], Positions).
        
генерация_позиций_коня(X, Y, N, Positions) :-
    генерация_позиций_коня(X, Y, N, [], Positions).


GOIT
генерация_позиций_коня(4, 4, 3, Positions)