actor(sane).
actor(insane).
thinks(_х,_у):-(_х=sane,call(_у)).
thinks(_х,_у):-(_х=insane,not(call(_у))).
ex(_king,_queen):-actor(_king),
actor(_queen),
thinks(_king,thinks(_queen,_king=insane)).
