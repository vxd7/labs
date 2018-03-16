:-op(50, fx, actor).
:-op(750, xfy, thinks_that).

actor sane.
actor insane.

X thinks_that Y:-(X=sane, call(Y)).
X thinks_that Y:-(X=insane, not(call(Y))).
ex0(King, Queen) :- 
    actor King,
    actor Queen,
    King thinks_that Queen thinks_that King=insane.
