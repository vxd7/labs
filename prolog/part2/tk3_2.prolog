has('Oleg', book('Pushkin', 'Kaptain''s daughter')).
has('Lenna', book('Monten', 'Opiti')).
has('Ira', handkerchief(blue)).
has('Lenna', handkerchief(red)).

% Who has ANY Monten's book
has_monten(Who) :- has(Who, book('Monten', _)).

% Who has what book
who_what_book(Who, Author, Title) :- has(Who, book(Author, Title)).

% Who has what
who_has_what(Who, What) :- has(Who, What).

% Lenna has blue handkerchief???
lenna_blue_handkerchief() :- has('Lenna', handkerchief(blue)).
