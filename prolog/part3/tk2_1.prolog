factorial(N, FactN) :- fact(N, FactN, 1, 1).
fact(N, FactN, I, P) :-
    I < N, 
    I1 is I + 1,
    P1 is P*I1,
    fact(N, FactN, I1, P1).
fact(N, FactN, N, FactN).
