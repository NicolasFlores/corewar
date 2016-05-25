.name "bigzork"
.comment "I know i cant win"

ld %0, r2   					;T_DIR(0) , T_REG(r2) charge 0 a l'adresse r2 (r1 + 1) 
st r1, 211						;T_REG(r1) , T_IND(211) stocke la valeur de r1 a l'adresse courante + 211 % IDX_MOD
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
st r1, 211						;T_REG , T_IND
loop:							; LABEL "loop"
live %1							;T_DIR(1) live a pour valeur 1
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
live %1							;T_DIR
zjmp %:loop						;T_DIR(%:loop) si carry a 1 saute a l'adresse de la valeur de loop
