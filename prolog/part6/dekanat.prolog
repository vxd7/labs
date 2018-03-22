:-dynamic(student/2).
:-dynamic(exam/5).

add_student(student(Name, Year)):-assert(student(Name, Year)).

out_all_students(student(Name, Year)):-
    student(Name, Year),
    write(student(Name, Year)), nl, fail.
out_all_students(_).

add_student_to_exam(exam(Subject, Date, StudentName)):-
    assert(exam(Subject, Date, StudentName, no_mark, no_mark)).

set_student_exam_mark(exam(Subject, Date, StudentName), Mark):-
    retract(exam(Subject, Date, StudentName, no_mark, no_mark)),
    assert(exam(Subject, Date, StudentName, Mark, no_mark)).

set_student_retake_mark(exam(Subject, Date, StudentName), RetakeMark):-
    exam(Subject, Date, StudentName, Mark, no_mark), % get exam mark
    retract(exam(Subject, Date, StudentName, Mark, no_mark)),
    assert(exam(Subject, Date, StudentName, Mark, RetakeMark)).

expell_students(student(Name, Year)):-
    retractall(exam(_, _, Name, _, _)),
    retractall(student(Name, Year)).

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

% Count students
count_students(student(Name, Year), _):-
    set_counter(num_of_students, 0),
    student(Name, Year),
    inc_counter(num_of_students, 1),
    fail.
count_students(_, Counter):-
    reset_counter(num_of_students, Counter).

count_students_by_exam(exam(Subject, Date), _):-
    set_counter(num_of_students_exam, 0),
    exam(Subject, Date, _, _, _),
    inc_counter(num_of_students_exam, 1),
    fail.
count_students_by_exam(_, Counter):-
    reset_counter(num_of_students_exam, Counter).

% Output functions
out_vedomost(exam(Subject, Date)):-
    exam(Subject, Date, StudentName, Mark, RetakeMark),
    write(exam(Subject, Date, StudentName, Mark, RetakeMark)), nl, fail.

out_failing_students_by_exam(exam(Subject, Date)):-
    exam(Subject, Date, StudentName, Mark, _),
    (Mark =< 4, !, student(StudentName, Year), write(student(StudentName, Year))), nl, fail.

add_test_students:-
    add_student(student('Ivan', 1)),
    add_student(student('Masha', 2)),
    add_student(student('Sasha', 3)),
    add_student(student('Kolya', 4)),
    add_student(student('Egor', 1)),

    add_student_to_exam(exam('Math', '02-01-18', 'Ivan')),
    add_student_to_exam(exam('Math', '02-01-18', 'Sasha')),
    add_student_to_exam(exam('Math', '02-01-18', 'Egor')),

    add_student_to_exam(exam('Geography', '28-02-18', 'Ivan')),
    add_student_to_exam(exam('Geography', '28-02-18', 'Masha')),
    add_student_to_exam(exam('Geography', '28-02-18', 'Kolya')).

% Menu
menu:-
    repeat,
    nl, nl, write('MENU'), nl,
    write('1. List of all students'), nl,
    write('2. List of students by exam (vedomost)'), nl,
    write('3. Add new student'), nl,
    write('4. Add student to exam'), nl,
    write('5. Expell student'), nl,
    write('6. Add exam mark'), nl,
    write('7. Add retake mark'), nl,
    write('8. List failing students'), nl,
    write('9. Get mean mark by subject'), nl,
    write('0. Exit'), nl, nl,
    write('Input the menu item number'), nl,
    read(X),
    handle_menu(X).

handle_menu(0):-!.
handle_menu(X):-menu_pt(X), fail.

menu_pt(1):- nl, write('List of all students:'), nl,
    out_all_students(_), !.

menu_pt(2):- nl, write('Input the subject and date of the exam:'), nl,
    write('Subject:'), nl, read(Subject),
    write('Date:'), nl, read(Date),
    out_vedomost(exam(Subject, Date)), !.

menu_pt(3):- nl, write('Input new student data:'), nl,
    write('Name:'), nl, read(Name),
    write('Year:'), nl, read(Year),
    add_student(student(Name, Year)), !.

menu_pt(4):- nl, write('Input student and exam related data:'), nl,
    write('Name of student:'), nl, read(StudentName),
    write('Subject of exam'), nl, read(Subject),
    write('Date of exam:'), nl, read(Date), 
    add_student_to_exam(exam(Subject, Date, StudentName)), !.

menu_pt(5):- nl, write('Input student info:'), nl,
    write('Name'), nl, read(StudentName),
    write('Year'), nl, read(Year), 
    expell_students(student(StudentName, Year)), !.

menu_pt(6):- nl, write('Input exam and student info:'), nl,
    write('Name of student:'), nl, read(StudentName),
    write('Subject of exam'), nl, read(Subject),
    write('Date of exam:'), nl, read(Date), 
    write('Mark:'), nl, read(Mark),
    set_student_exam_mark(exam(Subject, Date, StudentName), Mark), !.

menu_pt(7):- nl, write('Input exam and student info:'), nl,
    write('Name of student:'), nl, read(StudentName),
    write('Subject of exam'), nl, read(Subject),
    write('Date of exam:'), nl, read(Date), 
    write('Retake Mark:'), nl, read(Mark),
    set_student_retake_mark(exam(Subject, Date, StudentName), Mark), !.

menu_pt(8):- nl, write('List of failing students'), nl,
    write('Subject of exam'), nl, read(Subject),
    write('Date of exam:'), nl, read(Date), 
    out_failing_students_by_exam(exam(Subject, Date)), !.

menu_pt(_):-write('No such menu item, dumbass!'), nl, !.
