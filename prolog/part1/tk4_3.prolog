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

% Lives on the ground, but not a dog
lives_ground_not_dog(Who) :- lives(Who, ground), Who \= dog.

% Who lives in water and on the ground
lives_water_ground(Who) :- lives(Who, water), lives(Who, ground).

% Who lives only in one place
lives_only_one(Who, Where) :- lives(Who, Where), not((lives(Who, Where1), Where \= Where1)).

% Who lives at least in two places (two and more)
lives_atleast_two(Who, Where, Where1) :- lives(Who, Where), lives(Who, Where1), Where \= Where1.

% Who lives ONLY in two places
lives_only_two(Who, Where, Where1) :- lives_atleast_two(Who, Where, Where1), 
    not((lives(Who, Where2), Where2 \= Where1, Where2 \= Where)).

% ------------------------------------TASK1 ---------------------------------------------------------
do_not_intersect2(Who1, Who2) :- (lives(Who1, Where11), lives(Who1, Where12), Where11 \= Where12), 
    (lives(Who2, Where21), lives(Who2, Where22), Where21 \= Where22),
    (Where11 \= Where21, Where11 \= Where22, Where12 \= Where21, Where12 \= Where22), 
    Where11 @< Where12, Where21 @< Where22.

task1(Who1, Who2) :- lives_only_two(Who1, _, _), lives_only_two(Who2, _, _), Who1 \= Who2,
    do_not_intersect2(Who1, Who2).

who_where_not_lives(Who, Where1) :- lives(_, Where1), lives(Who, _), not(lives(Who, Where1)).
