grammar STIL;

///////////////////////////////////////////////////////////////////////
// RULES
///////////////////////////////////////////////////////////////////////

test: format? header? signals signal_groups; //timing scanstructures patternbursts patternexecs procedures;

///////////////////////////////////////////////////////////////////////

format      : 'STIL' FLOAT L_BRACKET design R_BRACKET;
design      : 'Design' INT;

///////////////////////////////////////////////////////////////////////

header      : 'Header' L_BRACKET title? date? source? history? R_BRACKET;
title       : 'Title' STRING;
date        : 'Date' STRING;
source      : 'Source' STRING;
history     : 'History' L_BRACKET annotation* R_BRACKET;
annotation  : 'Ann' L_BRACKET STRING R_BRACKET;

///////////////////////////////////////////////////////////////////////

signals             : 'Signals' ID? L_BRACKET signal* R_BRACKET;
signal              : ID signal_dir signal_attributes?;
signal_dir          : 'In' | 'Out' | 'InOut';
signal_attributes   : L_BRACKET signal_scan? char_map? R_BRACKET;
signal_scan         : 'Scan' ('In' | 'Out');
char_map            : 'WFCMap' L_BRACKET map_rule* R_BRACKET;
map_rule            : WFC WFC? '->' WFC;

///////////////////////////////////////////////////////////////////////

signal_groups       : 'SignalGroups' ID? L_BRACKET signal_group* R_BRACKET;
signal_group        : ID EQ QUOTATION signal_list QUOTATION signal_attributes?;
signal_list         : ID (SUM ID)*;




//timing          :;
//scanstructures  :;
//patternbursts   : patternburst*;
//patternburst    :;
//patternexecs    : patternexec*;
//patternexec     :;
//procedures      : procedure*;
//procedure       :;




///////////////////////////////////////////////////////////////////////
// TOKENS
///////////////////////////////////////////////////////////////////////

WFC         : LETTER | NUM;
SUM         : '+';
EQ          : '=';
SEMICOLON   : ';';
L_BRACKET   : '{';
R_BRACKET   : '}';
L_PAR       : '(';
R_PAR       : ')';
QUOTATION   : '\'';

INT     : NUM+;
FLOAT   : INT'.'INT;
NUM     : [0-9];

//\p{S}\p{P}\p{M}

//ID      : STRING | (LETTER (LETTER | '0'..'9')*);
ID      : STRING;
STRING  : '"' ([SPACE\p{S}\p{P}\p{M}\p{L}\p{N}])+ '"';
LETTER  : [a-zA-Z];

// White spaces ignored
WHITE_SPACES    : [ \t\r\n;]+ -> channel(99);
COMMENT         : '//' ~('\r' | '\n')* -> channel(99);