size(_,R):- R>=188,!,fail.
size(_,R):- R<158,!,fail.
size(5, R) :- R >= 182,!.
size(4, R) :- R >= 176,!.
size(3, R) :- R >= 170,!.
size(2, R) :- R >= 164,!.
size(1, R) :- R >= 158,!.

a:- write(1).
a:- write(2).
b(X):- a,X='еще'.
c:- a.
d:- a,fail.

country('England','London').
country('Russia','Moscow').
country('France','Paris').
country('China','Pekin').
country('Japan','Tokyo').
country('Italy','Rome').
ctr(Y) :- country(_, Y), write(Y), nl, fail.

r:- repeat, read(X), write(X), X=stop.

