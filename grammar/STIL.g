grammar STIL;

///////////////////////////////////////////////////////////////////////
// RULES
///////////////////////////////////////////////////////////////////////

test: format? header? signals signal_groups_l timings scan_structures pattern_bursts pattern_execs procedures_l;

///////////////////////////////////////////////////////////////////////

format  : 'STIL' FLOAT (L_BRACKET design R_BRACKET)?;
design  : 'Design' INT;

///////////////////////////////////////////////////////////////////////

header  : 'Header' L_BRACKET title? date? source? history? R_BRACKET;
title   : 'Title' string;
date    : 'Date' string;
source  : 'Source' string;
history : 'History' L_BRACKET R_BRACKET;

///////////////////////////////////////////////////////////////////////

signals             : 'Signals' ID? L_BRACKET signal* R_BRACKET;
signal              : ID signal_dir signal_attributes?;
signal_dir          : 'In' | 'Out' | 'InOut';
signal_attributes   : L_BRACKET signal_scan? char_map? R_BRACKET;
signal_scan         : 'ScanIn' | 'ScanOut';
char_map            : 'WFCMap' L_BRACKET map_rule* R_BRACKET;
map_rule            : wfc wfc? '->' wfc;

///////////////////////////////////////////////////////////////////////

signal_groups_l : signal_groups*;
signal_groups   : 'SignalGroups' ID? L_BRACKET signal_group* R_BRACKET;
signal_group    : ID EQ QUOTE signal_list QUOTE signal_attributes?;
signal_list     : ID (SUM ID)*;

///////////////////////////////////////////////////////////////////////

timings         : timing+;
timing          : 'Timing' ID? L_BRACKET waveform_table* R_BRACKET;
waveform_table  : 'WaveformTable' ID L_BRACKET period waveforms R_BRACKET;
period          : 'Period' time_expr;
waveforms       : 'Waveforms' L_BRACKET waveform* R_BRACKET;
waveform        : ID L_BRACKET wfc L_BRACKET event+ R_BRACKET R_BRACKET;
event           : time_expr event_code;
time_expr       : QUOTE num TIME_UNIT QUOTE;

///////////////////////////////////////////////////////////////////////

scan_structures : scan_structure*;
scan_structure  : 'void';

///////////////////////////////////////////////////////////////////////

pattern_bursts  : pattern_burst+;
pattern_burst   : 'PatternBurst' ID? L_BRACKET context pattern_list? R_BRACKET;
context         : signals_context? macro_context? proced_context?;
signals_context : 'SignalGroups' ID;
macro_context   : 'MacroDefs' ID;
proced_context  : 'Procedures' ID;
pattern_list    : 'PatList' L_BRACKET (pattern_call)* R_BRACKET;
pattern_call    : ID (L_BRACKET context R_BRACKET)?;

///////////////////////////////////////////////////////////////////////

pattern_execs       : pattern_exec+;
pattern_exec        : 'PatternExec' ID? L_BRACKET pattern_burst_call* R_BRACKET;
pattern_burst_call  : 'PatternBurst' ID;

///////////////////////////////////////////////////////////////////////

procedures_l    : procedures*;
procedures      : 'Procedures' ID? L_BRACKET procedure* R_BRACKET;
procedure       : ID L_BRACKET inst_list R_BRACKET;
inst_list       : (inst | loop)*;
inst            : (w_inst | c_inst | f_call | v_call | 'IddqTestPoint');
loop            : 'Loop' INT L_BRACKET inst_list R_BRACKET;
w_inst          : 'W' ID;
c_inst          : 'C' L_BRACKET assignations R_BRACKET;
f_call          : 'F' L_BRACKET assignations R_BRACKET;
v_call          : 'V' L_BRACKET assignations R_BRACKET;
assignations    : assignation*;
assignation     : ID EQ assig_expr;
assig_expr      : JOINING?


///////////////////////////////////////////////////////////////////////
// This is ugly but necessary, since the lexer doesn't know how to differentiate
// different tokens with with some intersection. For example, the lexical definition
// of an ID intersects with the definition of WFC, or events... Depending on the
// context there isn't ambiguity, but in the lexical analysis there isn't any context.
// To simplify and avoid some cases, we're going to consider that ALL ids are strings

num         : int_t | float_t;
int_t       : INT;
float_t     : FLOAT;
wfc         : ID | INT;
event_code  : ID;
string      : ID;

///////////////////////////////////////////////////////////////////////
// TOKENS
///////////////////////////////////////////////////////////////////////

TIME_UNIT   : 'ns' | 'ms' | 's';
SUM         : '+';
EQ          : '=';
SEMICOLON   : ';';
L_BRACKET   : '{';
R_BRACKET   : '}';
L_PAR       : '(';
R_PAR       : ')';
QUOTE       : '\'';

FLOAT   : INT'.'INT;
INT     : DIG+;

ID  : STRING | (LETTER (LETTER | DIG)*);

fragment DIG    : [0-9];
fragment NUM    : INT | FLOAT;
fragment LETTER : [a-zA-Z];
fragment STRING : '"' ~('\r' | '\n' | '"')* '"';

// Ignored tokens (Order is important)
WHITE_SPACES    : [ \t\r\n;]+ -> channel(99);
COMMENT         : '//' ~('\r' | '\n')* -> channel(99);
ANNOTATION      : 'Ann ' L_BRACKET '*' ([ \p{S}\p{P}\p{M}\p{L}\p{N}])* '*' R_BRACKET -> channel(99);