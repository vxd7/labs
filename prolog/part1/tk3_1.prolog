loves('Ellen', reading).
loves('Mark', computers).
loves('John', badminton).
loves('Eric', reading).

sport(badminton).
sport(tennis).
sport(football).
sport(baseball).

athlete(X) :- loves(X, Y), sport(Y).
