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
title   : 'Title' STRING;
date    : 'Date' STRING;
source  : 'Source' STRING;
history : 'History' L_BRACKET R_BRACKET;

///////////////////////////////////////////////////////////////////////

signals             : 'Signals' id? L_BRACKET signal* R_BRACKET;
signal              : id signal_dir signal_attributes?;
signal_dir          : 'In' | 'Out' | 'InOut';
signal_attributes   : L_BRACKET signal_scan? char_map? R_BRACKET;
signal_scan         : 'ScanIn' | 'ScanOut';
char_map            : 'WFCMap' L_BRACKET map_rule* R_BRACKET;
map_rule            : wfc wfc? '->' wfc;

///////////////////////////////////////////////////////////////////////

signal_groups_l : signal_groups*;
signal_groups   : 'SignalGroups' id? L_BRACKET signal_group* R_BRACKET;
signal_group    : id EQ QUOTE signal_list QUOTE signal_attributes?;
signal_list     : id (SUM id)*;

///////////////////////////////////////////////////////////////////////

timings         : timing+;
timing          : 'Timing' id? L_BRACKET waveform_table* R_BRACKET;
waveform_table  : 'WaveformTable' id L_BRACKET period waveforms R_BRACKET;
period          : 'Period' time_expr;
waveforms       : 'Waveforms' L_BRACKET waveform* R_BRACKET;
waveform        : id L_BRACKET wfc L_BRACKET event+ R_BRACKET R_BRACKET;
event           : time_expr event_code;
time_expr       : QUOTE num TIME_UNIT QUOTE;

///////////////////////////////////////////////////////////////////////

scan_structures : scan_structure*;
scan_structure  : 'void';

///////////////////////////////////////////////////////////////////////

pattern_bursts  : pattern_burst+;
pattern_burst   : 'PatternBurst' id? L_BRACKET context pattern_list? R_BRACKET;
context         : signals_context? macro_context? proced_context?;
signals_context : 'SignalGroups' id;
macro_context   : 'MacroDefs' id;
proced_context  : 'Procedures' id;
pattern_list    : 'PatList' L_BRACKET (pattern_call)* R_BRACKET;
pattern_call    : id (L_BRACKET context R_BRACKET)?;

///////////////////////////////////////////////////////////////////////

pattern_execs       : pattern_exec+;
pattern_exec        : 'PatternExec' id? L_BRACKET pattern_burst_call* R_BRACKET;
pattern_burst_call  : 'PatternBurst' id;

///////////////////////////////////////////////////////////////////////

procedures_l    : procedures*;
procedures      : 'Procedures' id? L_BRACKET procedure* R_BRACKET;
procedure       : id L_BRACKET inst_list R_BRACKET;
inst_list       : (inst | loop)*;
inst            : (w_inst | c_inst | f_call | v_call | 'IddqTestPoint');
loop            : 'Loop' INT L_BRACKET inst_list R_BRACKET;
w_inst          : 'W' id;
c_inst          : 'C' L_BRACKET assignations R_BRACKET;
f_call          : 'F' L_BRACKET assignations R_BRACKET;
v_call          : 'V' L_BRACKET assignations R_BRACKET;
assignations    : assignation*;
assignation     : id EQ assig_expr;
assig_expr      : JOIN?;


///////////////////////////////////////////////////////////////////////
// This is ugly but necessary, since the lexer doesn't know how to differentiate
// different tokens with with some intersection. For example, the lexical definition
// of an id intersects with the definition of WFC, or events... Depending on the
// context there isn't ambiguity, but in the lexical analysis there isn't any context.
// To simplify and avoid some cases, we're going to consider that ALL ids are strings

id          : STRING;
num         : int_t | float_t;
int_t       : INT;
float_t     : FLOAT;
wfc         : CHARS | INT;
event_code  : CHARS;

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
JOIN        : '\\j';

FLOAT   : INT'.'INT;
INT     : DIG+;
CHARS   : LETTER+;
STRING  : '"' ~('\r' | '\n' | '"')* '"';

fragment DIG    : [0-9];
fragment NUM    : INT | FLOAT;
fragment LETTER : [a-zA-Z];

// Ignored tokens (Order is important)
WHITE_SPACES    : [ \t\r\n;]+ -> channel(99);
COMMENT         : '//' ~('\r' | '\n')* -> channel(99);
ANNOTATION      : 'Ann ' L_BRACKET '*' ([ \p{S}\p{P}\p{M}\p{L}\p{N}])* '*' R_BRACKET -> channel(99);