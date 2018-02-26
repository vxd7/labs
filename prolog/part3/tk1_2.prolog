factorial(1, 1).
factorial(N, F) :-
    N > 1,
    N1 is N - 1,
    factorial(N1, F1),
    F is N*F1.

pow(_, 0, 1).
pow(X, Y, Ans) :-
    Y >= 0,
    Y1 is Y - 1, 
    pow(X, Y1, Ans1), 
    Ans is Ans1*X.
