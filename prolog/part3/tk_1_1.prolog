song(X) :- (X>1), write(' run '), (Y is X-1), song(Y).
song(1).
yaRun(X) :- write('Ya'), song(X), write('fucking run').
