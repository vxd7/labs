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

livesTwo(Who) :- lives(Who, Where1), lives(Who, Where2), Where1 \= Where2.
