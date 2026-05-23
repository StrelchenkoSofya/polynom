grammar polynom;

KF: '-'?[0-9]+'.'[0-9]+;
X: 'x';
Y: 'y';
Z: 'z';
DEG: [-]?[0-9][0]?;
DS: '^';
WS: [\t\r\n]+ -> skip;

ADD: '+';
SUB: '-';

polynom: op=(ADD | SUB)? monom #AddFirstMonom
    | polynom op=(ADD | SUB) monom #AddMonom
    ;

monom: koef? varx? vary? varz? #NewMonom
    ;

koef: KF #NewKoef;
varx: X degree? #NewX;
vary: Y degree? #NewY;
varz: Z degree? #NewZ;
degree: DS DEG #NewDeg;
