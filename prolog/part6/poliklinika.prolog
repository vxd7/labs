:-dynamic(patient/2).
:-dynamic(doctor/2).
:-dynamic(treats/4).

add_patient(patient(PatientName, PatientSurname), doctor(DoctorName, DoctorSurname), Symptom, Diagnosis):-
    assert(patient(PatientName, PatientSurname)),
    assert(treats(doctor(DoctorName, DoctorSurname), patient(PatientName, PatientSurname), Symptom, Diagnosis)).

add_doctor(doctor(DoctorName, DoctorSurname)):-
    assert(doctor(DoctorName, DoctorSurname)).

remove_patient(Patient):-
    retractall(treats(Patient, _, _, _)),
    retract(Patient).
remove_doctor(Doctor):-
    retractall(treats(_, Doctor, _, _)),
    retract(Doctor).

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
    ((Counter == Num), write(doctor(DoctorName, DoctorSurname)), nl), fail.
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

% TASKS
% TASK1 -------------------------------
max_patients_of_doctor(doctor(DoctorName, DoctorSurname), Count):-
    doctor(DoctorName, DoctorSurname),
    count_patients_of_doctor_with_diagnosis(doctor(DoctorName, DoctorSurname), _, Count),
    not((doctor(NewDoctorName, NewDoctorSurname), count_patients_of_doctor_with_diagnosis(doctor(NewDoctorName, NewDoctorSurname), _, Count1), Count < Count1)).

out_doctors_max_patients:-
    max_patients_of_doctor(_, Count), !, write(Count), nl, 
    out_doctors_treats_num_patients_with_diagnosis(Count, _).

% TASK2 ------------------------------
count_patient_diagnoses(patient(PatientName, PatientSurname), _):-
    patient(PatientName, PatientSurname),
    set_counter(patient_diagnoses, 0),
    treats(_, patient(PatientName, PatientSurname), _, _),
    inc_counter(patient_diagnoses, 1), fail.
count_patient_diagnoses(_, Counter):-
    reset_counter(patient_diagnoses, Counter).

max_diagnoses_of_patient(patient(PatientName, PatientSurname), Count):-
    patient(PatientName, PatientSurname),
    count_patient_diagnoses(patient(PatientName, PatientSurname), Count),
    not((patient(NewPatientName, NewPatientSurname), count_patient_diagnoses(patient(NewPatientName, NewPatientSurname), Count1), Count < Count1)).

out_patients_max_diagnoses:-
    max_diagnoses_of_patient(_, Count), !, write(Count), nl,
    patient(PatientName, PatientSurname),
    count_patient_diagnoses(patient(PatientName, PatientSurname), Counter1),
    (Count == Counter1, write(patient(PatientName, PatientSurname)), nl), fail.



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

add_test_doctors_patients:-
    add_doctor(doctor('Doctor1Name', 'Doctor1Surname')),
    add_doctor(doctor('Doctor2Name', 'Doctor2Surname')),  % Doctors have same surname
    add_doctor(doctor('Doctor2Name_1', 'Doctor2Surname')),%
    add_doctor(doctor('Doctor3Name', 'Doctor3Surname')),
    add_doctor(doctor('Doctor4Name', 'Doctor4Surname')),
    add_doctor(doctor('Doctor5Name', 'Doctor5Surname')),
    add_doctor(doctor('Doctor6Name', 'Doctor6Surname')),
    add_doctor(doctor('Doctor8Name', 'Doctor8Surname')),

    add_patient(patient('Patient1Name', 'Patient1Surname'), doctor('Doctor1Name', 'Doctor1Surname'), symptom1, diagnos1),   %
    add_patient(patient('Patient2Name', 'Patient2Surname'), doctor('Doctor1Name', 'Doctor1Surname'), symptom2, diagnos2),   % Patients of Doctor1
    add_patient(patient('Patient3Name', 'Patient3Surname'), doctor('Doctor1Name', 'Doctor1Surname'), symptom3, diagnos3),   %

    add_patient(patient('Patient4Name', 'Doctor2Surname'), doctor('Doctor2Name', 'Doctor2Surname'), symptom4, diagnos4),    % Patient 4 has same surname as doctor2

    add_patient(patient('Patient5Name', 'Patient5Surname'), doctor('Doctor3Name', 'Doctor3Surname'), symptom11, diagnos4),  %
    add_patient(patient('Patient6Name', 'Patient6Surname'), doctor('Doctor3Name', 'Doctor3Surname'), symptom11, diagnos4),  % 3 patients have same doctor and same diagnosis
    add_patient(patient('Patient7Name', 'Patient7Surname'), doctor('Doctor3Name', 'Doctor3Surname'), symptom13, diagnos4),  %

    add_patient(patient('Patient8Name', 'Patient8Surname'), doctor('Doctor4Name', 'Doctor4Surname'), symptom21, diagnos4),  %
    add_patient(patient('Patient9Name', 'Patient9Surname'), doctor('Doctor4Name', 'Doctor4Surname'), symptom22, diagnos4),  % 3 patients have same doctor and same diagnosis
    add_patient(patient('Patient10Name', 'Patient10Surname'), doctor('Doctor4Name', 'Doctor4Surname'), symptom23, diagnos4),%

    add_patient(patient('Patient11Name', 'Patient11Surname'), doctor('Doctor5Name', 'Doctor5Surname'), symptom31, diagnos5),%
    add_patient(patient('Patient12Name', 'Patient12Surname'), doctor('Doctor5Name', 'Doctor5Surname'), symptom32, diagnos4),% Patients of doctor5 have same diagnosis as
    add_patient(patient('Patient13Name', 'Patient13Surname'), doctor('Doctor6Name', 'Doctor6Surname'), symptom33, diagnos4),% patients of doctor6

    add_patient(patient('PatientDName', 'PatientDSurname'), doctor('Doctor6Name', 'Doctor6Surname'), symptom33, diagnos9),
    add_patient(patient('PatientDName', 'PatientDSurname'), doctor('Doctor2Name', 'Doctor2Surname'), symptom33, diagnos0),
    add_patient(patient('PatientDName', 'PatientDSurname'), doctor('Doctor8Name', 'Doctor8Surname'), symptom33, diagnos01).

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
    write('8. Delete patient'), nl,
    write('9. Delete doctor'), nl,
    write('10. Doctors who treat max number of patients'), nl,
    write('11. Patients with max number of diagnoses'), nl,
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
    add_test_doctors_patients,
    write('Done!'), !.

menu_pt(8):-nl, write('Input patient'), nl,
    read(Patient),
    remove_patient(Patient), !.
menu_pt(9):-nl, write('Input doctor'), nl,
    read(Doctor),
    remove_doctor(Doctor), !.

menu_pt(10):-nl,
    out_doctors_max_patients, !.

menu_pt(11):-nl,
    out_patients_max_diagnoses, !.
menu_pt(_):-write('No such menu item, dumbass!'), nl, !.
