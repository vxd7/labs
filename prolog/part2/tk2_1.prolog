% car(Name, Price, Color, Age) - predicate
car(moskvich, 9500, green, 1).
car(moskvich, 3000, blue, 5).
car(volga, 15000, black, 1).
car(volga, 8000, white, 6).
car('UAZ', 9000, green, 3).
car('VAZ', 6000, white, 4).
car('VAZ', 4000, blue, 10).
car('VAZ-2108', 8000, gray, 2).

% tk b) price < 5000
car_price_less_5000(Name, Price) :- car(Name, Price, _, _), Price < 5000.

% tk c) worth buying
worth_buying(Name, Target_price) :- car(Name, P, C, A), (C = green ; C = blue), P < Target_price, A < 3.

% tk d) What cars can be bought for 10000
cars_for_10000(Name, Price) :- car(Name, Price, _, _), Price =< 10000.
