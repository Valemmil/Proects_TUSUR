% Facts
itis(kesha, bird).
itis(cat, friend).
like(bird, warm).
like(cat, fish).
like(friend, friend).

% Rule
eating_this(Who, Eat) :-
    ((Who \== cat, Who \== bird) -> itis(Who, Animal); like(Who, Eat)),
    like(Animal, Eat).
	

GOIT
eating_this(kesha, What1),
	eating_this(cat, What2).