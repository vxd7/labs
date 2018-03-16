lives(zebra, ground).
lives(dog, ground).
lives(carp, ground).
lives(whale, water).

lives(cat, X) :- lives(dog, X).

lives(crocodile, water).
lives(crocodile, ground).

lives(frog, water).
lives(frog, ground).

lives(duck, water).
lives(duck, ground).
lives(duck, air).

lives(eagle, air).
lives(eagle, ground).

lives(bourevestnik, water).
lives(bourevestnik, air).

lives(spaceman, ground).
lives(spaceman, space).

animal(zebra).
animal(dog).
animal(carp).
animal(whale).
animal(cat).
animal(crocodile).
animal(frog).
animal(duck).
animal(eagle).
animal(bourevestnik).

lives_atleast_two_snip(Who, Where, Where1) :- animal(Who), tt(Who, Where, Where1).
tt(Who, Where, Where1) :- lives(Who, Where), lives(Who, Where1), Where \= Where1, !.
