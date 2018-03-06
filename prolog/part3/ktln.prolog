% Рекурсивный предикат для генерации чисел Каталана
% N -- номер числа Каталана, индексация с нуля
ktln(N, Res) :- ktln_func(N, 0, 0, Res), !.
ktln_func(N, I, Sum, X) :-
    I =< N - 1,
    ktln_func(I, 0, 0, C1),
    Ic is N - 1 - I,
    ktln_func(Ic, 0, 0, C2),
    Sum1 is Sum + C1 * C2,
    I1 is I + 1,
    ktln_func(N, I1, Sum1, X).
ktln_func(0, _, _, 1).
ktln_func(N, N, X, X).

% Предикат, проверяющий, является ли введенное число 
% N числом Каталана. Если да, то найти его номер, 
% если нет, вывести сообщение об ошибке
check_if_ktln(N, X) :- check_if_ktln_func(N, X, 0).
check_if_ktln_func(N, X, I) :-
    I1 is I + 1,
    ktln(I1, K),
    (K == N, !, X is I1);
    
    I1 is I + 1,
    ktln(I1, K),
    (K >= N, !, write('No such number exists '), fail);
    
    I1 is I + 1,
    check_if_ktln_func(N, X, I1).

% Рекурсивный предикат для вычисления факториала
fact(N, X) :- fact_func(N, X, 1, 1), !.
fact_func(N, X, I, Mul) :-
    I1 is I + 1,
    I1 =< N,
    Mul1 is Mul * I1,
    fact_func(N, X, I1, Mul1).
fact_func(N, X, N, X).

% Предикат для вычисления биномиальных коэффициентов
binomial_coeff(N, M, X) :- 	
    M > N, 
    X is 0.

binomial_coeff(N, M, X) :- 	
    fact(N, FactN),
    fact(M, FactM),
    NM is N - M,
    fact(NM, FactNM),
    X is FactN/(FactM * FactNM).

% Предикат для вычисления элементов треугольника Паскаля
% Указываются номер строки и номер элемента
pascal_triangle_elem(RowNum, ElemNum, X) :-
    ElemNum =< RowNum,
    binomial_coeff(RowNum, ElemNum, X).
