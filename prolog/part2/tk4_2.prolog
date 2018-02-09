% ---------- pt a)
has('Ivan', rub(10000)).
has('Ivan', tv).
has('Ivan', car('Volga', cherry)).
has('Ivan', radio).

has('Pyotr', rub(5000)).
has('Pyotr', tv).
has('Pyotr', refrigerator).

has('Kolya', rub(20000)).
has('Kolya', tv).

% ---------- pt b)
% What does Petr have?
what_petr_has(What) :- has('Pyotr', What).

% Who has 10000 RUB
who_has_10000(Who) :- has(Who, rub(10000)).

% Things Ivan has, but Nikolay doesn't (except money)
ivan_has_nico_doesnt(What) :- has('Ivan', What), not(has('Kolya', What)), What \= rub(_).

% ---------- pt c)
price(car('Volga'), 32000).
price(tv, 8400).
price(refrigerator, 4200).
price(radio, 3500).
price(video, 12000).
price(priyomnik, 1300).
price(watches, 500).

% ---------- pt d)
% Can Pyotr buy a video?
can_petr_video() :- has('Pyotr', rub(Amount)), price(video, Price), Amount >= Price.

% Has max money
has_max_money(Who, Amount) :- has(Who, rub(Amount)), not((has(_, rub(Amount1)), Amount < Amount1)).

% ---------- pt e)
can_buy(Person, Thing) :- has(Person, rub(Amount)), price(Thing, Price), Amount >= Price, not(has(Person, Thing)).

% ---------- pt f)
% What can Kolya buy?
% can_buy('Kolya', What).

% What can Kolya buy which Ivan has?
can_kolya_ivan_has(What) :- can_buy('Kolya', What), has('Ivan', What).

% ---------- pt. g)
is_wife('Anna', 'Kolya').
is_wife('Maria', 'Ivan').
is_wife('Olga', 'Pyotr').

% ---------- pt h)
has(Woman, Thing):- is_wife(Woman, Man), has(Man, Thing).

% ---------- pt i)
% Does Maria have a car?
maria_car() :- has('Maria', car(_, _)).

% What can Anna buy which doesn't Maria have?
anna_buy_maria_not_have(Thing) :- can_buy('Anna', Thing), not(has('Maria', Thing)).
