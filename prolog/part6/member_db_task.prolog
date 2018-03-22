:- dynamic(member/3).

contrib(Age, rub(1)):-Age < 18.
contrib(Age, rub(2)):-Age >= 18.

new_member(member(Surname, Age, Payment_Data)) :- assert(member(Surname, Age, Payment_Data)).

output_data(member(Surname, Age, Payment_Data)):-
    member(Surname, Age, Payment_Data),
    contrib(Age, Summa),
    write(member(Surname, Age, Summa, Payment_Data)), nl, fail.
output_dat(_).

del_all(Member) :- retractall(Member).

has_paid(member(Surname, Age)):-
    retract(member(Surname, Age, not_paid)),
    assert(member(Surname, Age, paid)).

task :-
    new_member(member('Pronin', 45, paid)),
    new_member(member('Sidorov', 27, not_paid)),
    new_member(member('Danilov', 12, not_paid)),
    new_member(member('Ivanov', 15, paid)),
    new_member(member('Ivanov', 33, not_paid)),
    new_member(member('Chromov', 40, not_paid)),
    output_data(_).

% Counters
set_counter(Name, Start) :- 
    retractall(counter(Name, _)),
    assert(counter(Name, Start)).

inc_counter(Name, Increment) :-
    retract(counter(Name, Value)),
    New_value is Value + Increment,
    assert(counter(Name, New_value)).

reset_counter(Name, Value):-
    retract(counter(Name, Value)).

% Count all the members in db
count_members(member(Surname, Age, Payment_Data), _) :-
    set_counter(num_of_members, 0),
    member(Surname, Age, Payment_Data),
    inc_counter(num_of_members, 1),
    fail.
count_members(_, Counter):-
    reset_counter(num_of_members, Counter).

% Menu
menu:-
    repeat,
    nl, nl, write('MENU'), nl,
    write('1. Info about club members'),          nl,
    write('2. Count the number of club members'), nl,
    write('3. Add info to database'),             nl,
    write('4. Delete info from database'),        nl,
    write('5. Add payment info'),                 nl,
    write('6. Delete non-payers'),                nl,
    write('7. Count the number of non-payers'),   nl,
    write('0. Exit'),                             nl, nl,
    write('Input the menu item number '),         nl,
    read(X),
    handle_menu(X).

handle_menu(0):-!.
handle_menu(X):-menu_pt(X), fail.

menu_pt(1):- nl, write('Club members:'),
    nl, output_data(_), !.

menu_pt(2):-nl, count_members(member(_, _, _), Count),
    write('Number of club members = '), write(Count), nl, !.

menu_pt(3):-nl, write('Input new member data '), nl,
    write('Surname '),   nl, read(Surname),
    write('Age '),       nl, read(Age),
    write('Has paid? '), nl, read(Payment_Data),
    new_member(member(Surname, Age, Payment_Data)), !.

menu_pt(4):-nl, write('Input data about person who you want to delete:'), nl,
    write('Surname '),      nl, read(Surname),
    write('Age '),          nl, read(Age),
    write('Payment info '), nl, read(Payment_Data),
    retract(member(Surname, Age, Payment_Data)), nl, !.

menu_pt(5):-nl, write('Input data about person:'), nl,
    write('Surname '), nl, read(Surname),
    write('Age '),     nl, read(Age),
    has_paid(member(Surname, Age)), nl, !.

menu_pt(6):-nl,
    del_all(member(_, _, not_paid)), nl, !.

menu_pt(7):-nl, count_members(member(_, _, not_paid), Count),
    write('Number of non-payers = '), write(Count), nl, !.

menu_pt(_):-write('No such menu item, dumbass!'), nl, !.
