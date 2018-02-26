factorial(N, FactN) :- fact(N, FactN, 1).
fact(N, FactN, P) :-
    N>0,
    P1 is P*N,
    N1 is N-1,
    fact(N1, FactN, P1).
fact(0, FactN, FactN).
