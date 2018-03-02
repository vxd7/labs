% >>> Zadanie 3.2
% Числа Фибоначчи, рекурсивный предикат без накопительных переменных
fibb_nonakop(1, 1).
fibb_nonakop(2, 1).
fibb_nonakop(N, X) :-
    N >= 1,
    N1 is N-1,
    N2 is N-2,
    fibb_nonakop(N1, P1),
    fibb_nonakop(N2, P2),
    X is P1 + P2.

% Числа Фибоначчи с накопительными переменными
fibb_nkp(N, X) :- N>= 1, fibb_nakop(N, X, 1, 1, 0).
fibb_nakop(N, X, I, Cur, Prev) :-
    I < N,
    Nxt is Cur + Prev,
    I1 is I + 1,
    fibb_nakop(N, X, I1, Nxt, Cur).
fibb_nakop(N, X, N, X, _).

% If number is even or odd
even(X) :-
    0 is X mod 2.
odd(X) :- 
    not(even(X)).

% If number even -- Y = X. Else Y = 0
evenPair(X, Y) :- even(X), !, Y is X.
evenPair(_, 0).

oddPair(X, Y) :- odd(X), !, Y is X.
oddPair(_, 0).

% >>> Zadanie 3.3
% Сумма нечетных чисел из первых N чисел Фибоначчи
fibb_sum_odd(N, X) :- fibb_sum_func_odd(N, X, 0, 0).
fibb_sum_func_odd(N, X, I, Sum) :-
    I < N, 
    I1 is I + 1,
    fibb_nkp(I1, Cur),
    oddPair(Cur, Cur1),
    Sum1 is Sum + Cur1, 
    fibb_sum_func_odd(N, X, I1, Sum1).
fibb_sum_func_odd(N, X, N, X).

% Сумма четных чисел из первых N чисел Фибоначчи
fibb_sum_even(N, X) :- fibb_sum_func_even(N, X, 0, 0).
fibb_sum_func_even(N, X, I, Sum) :-
    I < N, 
    I1 is I + 1,
    fibb_nkp(I1, Cur),
    evenPair(Cur, Cur1),
    Sum1 is Sum + Cur1, 
    fibb_sum_func_even(N, X, I1, Sum1).
fibb_sum_func_even(N, X, N, X).


% Task 3.4
%check_if_odd_fibb(N, X) :- fibb_check_odd(N, X, 0, 0).
%fibb_check_odd(N, X, I, CurSum) :-
%    CurSum =< N,
%    I1 is I + 1,
%    fibb_sum_odd(I1, Sum),
%    (((Sum == N), !, Sum1 is N + N) ; Sum1 is Sum), % N + N because we want to end cycle
%    fibb_check_odd(N, X, I1, Sum1).
%fibb_check_odd(_, X, X, _).

% Предикат, проверяющий, является ли N суммой нечетных чисел из первых n чисел фибоначчи.
% Вычисляет n в аргументе X
check_fibb_odd(N, X) :- check_odd_func(N, X, 0).
check_odd_func(N, X, I) :-
    I1 is I + 1,
    fibb_sum_odd(I1, Sum),
    (Sum == N, !, X is I1); I1 is I + 1, fibb_sum_odd(I1, Sum), Sum < N, check_odd_func(N, X, I1).

% Предикат, проверяющий, является ли N суммой четных чисел из первых n чисел фибоначчи.
% Вычисляет n в аргументе X
check_fibb_even(N, X) :- check_even_func(N, X, 0).
check_even_func(N, X, I) :-
    I1 is I + 1,
    fibb_sum_even(I1, Sum),
    (Sum == N, !, X is I1); I1 is I + 1, fibb_sum_even(I1, Sum), Sum < N, check_even_func(N, X, I1).

% Реализация функции Аккермана. X, Y -- неотрицательные
m_akkerman(0, Y, RES) :- RES is Y + 1.
m_akkerman(X, 0, RES) :- X > 0, X1 is X - 1, m_akkerman(X1, 1, RES).
m_akkerman(X, Y, RES) :- X > 0, Y > 0, 
    Y1 is Y - 1, m_akkerman(X, Y1, RES1), 
    X1 is X - 1, m_akkerman(X1, RES1, RES).
