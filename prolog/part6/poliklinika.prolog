:-dynamic(patient/2).
:-dynamic(doctor/2).
:-dynamic(treats/4).

add_patient(patient(PatientName, PatientSurname), doctor(DoctorName, DoctorSurname), Symptom, Diagnosis):-
    assert(patient(PatientName, PatientSurname)),
    assert(treats(doctor(DoctorName, DoctorSurname), patient(PatientName, PatientSurname), Symptom, Diagnosis)).

add_doctor(doctor(DoctorName, DoctorSurname)):-
    assert(doctor(DoctorName, DoctorSurname)).

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

% Output funcs
out_patients_with_diagnosis(Diagnosis):-
    patient(PatientName, PatientSurname),
    treats(_, patient(PatientName, PatientSurname),  _, Diagnosis),
    write(patient(PatientName, PatientSurname)), nl,
    fail.
out_patients_with_diagnosis(_).

out_patients_whom_treats_same_doctor_as(patient(PatientName, PatientSurname)):-
    doctor(DoctorName, DoctorSurname),
    patient(PatientName, PatientSurname),
    treats(doctor(DoctorName, DoctorSurname), patient(PatientName, PatientSurname),  _, _), !,
    treats(doctor(DoctorName, DoctorSurname), patient(NewPatientName, NewPatientSurname), _, _),
    write(patient(NewPatientName, NewPatientSurname)), nl,
    fail.
out_patients_whom_treats_same_doctor_as(_).

out_doctors_same_surname_as_patient(PatientSurname):-
    doctor(DoctorName, PatientSurname),
    write(doctor(DoctorName, PatientSurname)), nl,
    fail.
out_doctors_same_surname_as_patient(_).

count_patients_of_doctor_with_diagnosis(doctor(DoctorName, DoctorSurname), Diagnosis, _):-
    doctor(DoctorName, DoctorSurname),
    set_counter(patients_of_doctor_with_diagnosis, 0),
    treats(doctor(DoctorName, DoctorSurname), patient(_, _), _, Diagnosis),
    inc_counter(patients_of_doctor_with_diagnosis, 1), fail.
count_patients_of_doctor_with_diagnosis(_, _, Counter):-
    reset_counter(patients_of_doctor_with_diagnosis, Counter).

out_doctors_treats_num_patients_with_diagnosis(Num, Diagnosis):-
    doctor(DoctorName, DoctorSurname),
    count_patients_of_doctor_with_diagnosis(doctor(DoctorName, DoctorSurname), Diagnosis, Counter),
    ((Counter == Num), !, write(doctor(DoctorName, DoctorSurname)), nl), fail.
out_doctors_treats_num_patients_with_diagnosis(_).

out_patients_same_symptoms_as(patient(PatientName, PatientSurname)):-
    treats(_, patient(PatientName, PatientSurname), Symptoms, _), !,
    treats(_, patient(NewPatientName, NewPatientSurname), Symptoms, _),
    write(patient(NewPatientName, NewPatientSurname)), nl, fail.
out_patients_same_symptoms_as(_).

out_patients_of_doctor_A_with_same_diagnosis_as_patients_of_doctor_B(doctor(DoctorAName, DoctorASurname), 
    doctor(DoctorBName, DoctorBSurname), patient(PatientName, PatientSurname)):-
        treats(doctor(DoctorBName, DoctorBSurname), patient(PatientName, PatientSurname), _, Diagnosis), !,
        treats(doctor(DoctorAName, DoctorASurname), patient(NewPatientName, NewPatientSurname), _, Diagnosis),
        write(patient(NewPatientName, NewPatientSurname)), nl, fail.
out_patients_of_doctor_A_with_same_diagnosis_as_patients_of_doctor_B(_).

add_doctors_patients:-
    add_doctor(doctor('Ivan', 'Ivanov')),
    add_doctor(doctor('Ivan111', 'Ivanov')),
    add_doctor(doctor('Maria', 'Alexandrova')),
    add_doctor(doctor('Sergey', 'Upirev')),
    add_doctor(doctor('Alex', 'K')),

    add_patient(patient('PatientA', 'Ivanov'), doctor('Maria', 'Alexandrova'), headache, idiot),
    add_patient(patient('PatientB', 'PatientBSurname'), doctor('Ivan', 'Ivanov'), blood_everuwhere, dead),

    add_patient(patient('PatientC', 'PatientCSurname'), doctor('Sergey', 'Upirev'), headache, idiot),
    add_patient(patient('PatientD', 'PatientDSurname'), doctor('Alex', 'K'), blood_everuwhere, dead),

    add_patient(patient('PatientE', 'PatientESurname'), doctor('Ivan', 'Ivanov'), headache, idiot),
    add_patient(patient('PatientF', 'PatientFSurname'), doctor('Ivan', 'Ivanov'), something, idiot).

% Menu
menu:-
    repeat,
    nl, nl, write('MENU'), nl,
    write('1. Список всех пациентов с заданным диагнозом'), nl,
    write('2. Cписок пациентов, которые обслуживаются тем же доктором, что и заданный пациент'), nl,
    write('3. Получить список докторов- однофамильцев с заданным пациентом'), nl,
    write('4. Получить список докторов, у которых лечатся пациенты не меньше заданного количества с заданным диагнозом'), nl,
    write('5. Получить список пациентов, имеющих те же симптомы болезни, что и у заданного пациента'), nl,
    write('6. Для заданного доктора «А» получить список его пациентов, имеющих тот же диагноз, что и выбранный пациент, лечащийся у доктора «В»'), nl,
    write('7. Добавить примерный список докторов и пациентов для тестинга'), nl,
    write('0. Exit'), nl, nl,
    write('Input the menu item number'), nl,
    read(X),
    handle_menu(X).

handle_menu(0):-!.
handle_menu(X):-menu_pt(X), fail.

menu_pt(1):- nl, write('List of all patients with diagnosis:'), nl,
    write('Input Diagnosis:'), nl, read(Diagnosis),
    out_patients_with_diagnosis(Diagnosis), !.

menu_pt(2):- nl, write('Input the patient name:'), nl,
    write('Patient name:'), nl, read(PatientName),
    write('Patient Surname:'), nl, read(PatientSurname),
    out_patients_whom_treats_same_doctor_as(patient(PatientName, PatientSurname)), !.

menu_pt(3):- nl, write('Input patient surname:'), nl,
    write('Patient Surname:'), nl, read(PatientSurname),
    out_doctors_same_surname_as_patient(PatientSurname), !.

menu_pt(4):- nl, write('Input data:'), nl,
    write('Num:'), nl, read(Num),
    write('Diagnosis'), nl, read(Diagnosis),
    out_doctors_treats_num_patients_with_diagnosis(Num, Diagnosis), !.

menu_pt(5):- nl, write('Input patient name:'), nl,
    write('Patient Name'), nl, read(PatientName),
    write('Patient Surname'), nl, read(PatientSurname), 
    out_patients_same_symptoms_as(patient(PatientName, PatientSurname)), !.

menu_pt(6):- nl, write('Input doctor A, doctor B, patient of doctor B info:'), nl,
    write('Doctor A name:'), nl, read(DoctorAName),
    write('Doctor A surname'), nl, read(DoctorASurname),
    write('Doctor B name:'), nl, read(DoctorBName),
    write('Doctor B surname'), nl, read(DoctorBSurname),
    write('Patient name:'), nl, read(PatientName),
    write('Patient surname'), nl, read(PatientSurname),
    out_patients_of_doctor_A_with_same_diagnosis_as_patients_of_doctor_B(doctor(DoctorAName, DoctorASurname),
    doctor(DoctorBName, DoctorBSurname), patient(PatientName, PatientSurname)), !.

menu_pt(7):-nl, write('Adding patients and doctors...'), nl,
    add_doctors_patients,
    write('Done!'), !.

menu_pt(_):-write('No such menu item, dumbass!'), nl, !.
