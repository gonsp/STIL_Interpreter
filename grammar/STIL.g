grammar STIL;

///////////////////////////////////////////////////////////////////////
// RULES
///////////////////////////////////////////////////////////////////////

test: format? header? signals signal_groups timing; // scanstructures patternbursts patternexecs procedures;

///////////////////////////////////////////////////////////////////////

format      : 'STIL' FLOAT L_BRACKET design R_BRACKET;
design      : 'Design' INT;

///////////////////////////////////////////////////////////////////////

header      : 'Header' L_BRACKET title? date? source? history? R_BRACKET;
title       : 'Title' STRING;
date        : 'Date' STRING;
source      : 'Source' STRING;
history     : 'History' L_BRACKET annotation* R_BRACKET;
annotation  : 'Ann' L_BRACKET ANN R_BRACKET;

///////////////////////////////////////////////////////////////////////

signals             : 'Signals' ID? L_BRACKET signal* R_BRACKET;
signal              : ID signal_dir signal_attributes?;
signal_dir          : 'In' | 'Out' | 'InOut';
signal_attributes   : L_BRACKET signal_scan? char_map? R_BRACKET;
signal_scan         : 'Scan' ('In' | 'Out');
char_map            : 'WFCMap' L_BRACKET map_rule* R_BRACKET;
map_rule            : WFC WFC? '->' WFC;

///////////////////////////////////////////////////////////////////////

signal_groups   : 'SignalGroups' ID? L_BRACKET signal_group* R_BRACKET;
signal_group    : ID EQ QUOTATION signal_list QUOTATION signal_attributes?;
signal_list     : ID (SUM ID)*;

///////////////////////////////////////////////////////////////////////

timing          : 'Timing' ID? L_BRACKET waveform_table* R_BRACKET;
waveform_table  : 'WaveformTable' ID L_BRACKET period waveforms R_BRACKET;
period          : 'Period' time_expr;
waveforms       : 'Waveforms' L_BRACKET waveform* R_BRACKET;
waveform        : ID L_BRACKET WFC L_BRACKET event+ R_BRACKET R_BRACKET;
event           : time_expr EVENT_CODE;
time_expr       : QUOTATION (INT | FLOAT) TIME_UNIT QUOTATION;

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

TIME_UNIT   : 'ns' | 'ms' | 's';
fragment WFC: LETTER | INT;

SUM         : '+';
EQ          : '=';
SEMICOLON   : ';';
L_BRACKET   : '{';
R_BRACKET   : '}';
L_PAR       : '(';
R_PAR       : ')';
QUOTATION   : '\'';

FLOAT   : INT'.'INT;
INT     : DIG+;

ID  : STRING | (LETTER (LETTER | DIG)*);
ANN : '*' (ALL | '"')* '*';

fragment STRING : '"' ALL* '"';
fragment ALL    : [SPACE\p{S}\p{P}\p{M}\p{L}\p{N}];
fragment LETTER : [a-zA-Z];
fragment DIG    : [0-9];
fragment NUM    : INT | FLOAT;

// White spaces ignored
WHITE_SPACES    : [ \t\r\n;]+ -> channel(99);
COMMENT         : '//' ~('\r' | '\n')* -> channel(99);