actor(sane).
actor(insane).
thinks(_х,_у):-(_х=sane,call(_у)).
thinks(_х,_у):-(_х=insane,not(call(_у))).
ex(_valet):-
    actor(_valet),
    actor(_triple),
    actor(_four),
    actor(_five),
    actor(_six),
    actor(_seven),
    actor(_double),
    actor(_tuz),
  thinks(_triple,_tuz=insane),
  thinks(_four, (not((_triple=insane, _double=insane)))),

  thinks(_five, ((_tuz=insane, _four=insane) ; (_tuz=sane, _four=sane))),

  thinks(_six, (_tuz=sane, _double=sane)),
  thinks(_seven,_five=insane),
  thinks(_valet,(not((_six=insane, _seven=insane)))).

% ?- ex(Valet).
