grammar STIL;

///////////////////////////////////////////////////////////////////////
// RULES
///////////////////////////////////////////////////////////////////////

program : format? header? signals signal_groups timing_l scan_structures_l
          pattern_burst_l pattern_exec_l procedures_l macros_l pattern_l EOF;

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

signals             : 'Signals' L_BRACKET signal* R_BRACKET;
signal              : id signal_dir signal_attributes?;
signal_dir          : 'In' | 'Out' | 'InOut';
signal_attributes   : L_BRACKET signal_scan? wfc_map? R_BRACKET;
signal_scan         : 'ScanIn' | 'ScanOut';
wfc_map            : 'WFCMap' L_BRACKET map_rule* R_BRACKET;
map_rule            : wfc '->' wfc;

///////////////////////////////////////////////////////////////////////

signal_groups   : 'SignalGroups' L_BRACKET signal_group* R_BRACKET;
signal_group    : id EQ QUOTE signal_list QUOTE signal_attributes?;
signal_list     : id (SUM id)*;

///////////////////////////////////////////////////////////////////////

timing_l         : timing+;
timing          : 'Timing' id? L_BRACKET waveform_table* R_BRACKET;
waveform_table  : 'WaveformTable' id L_BRACKET period waveforms R_BRACKET;
period          : 'Period' time_expr;
waveforms       : 'Waveforms' L_BRACKET waveform* R_BRACKET;
waveform        : id L_BRACKET wfc L_BRACKET event+ R_BRACKET R_BRACKET;
event           : time_expr event_code;
time_expr       : QUOTE num TIME_UNIT QUOTE;

///////////////////////////////////////////////////////////////////////

scan_structures_l   : scan_structures*;
scan_structures     : 'ScanStructures' id? L_BRACKET scan_chain* R_BRACKET;
scan_chain          : 'ScanChain' id L_BRACKET scan_length scan_in scan_out
                      scan_inversion scan_cells scan_clock R_BRACKET;
scan_length         : 'ScanLength' INT;
scan_in             : 'ScanIn' id;
scan_out            : 'ScanOut' id;
scan_inversion      : 'ScanInversion' INT;
scan_cells          : 'ScanCells' (id EXCLAMATION?)+;
scan_clock          : 'ScanMasterClock' id?;

///////////////////////////////////////////////////////////////////////

pattern_burst_l : pattern_burst+;
pattern_burst   : 'PatternBurst' id L_BRACKET context pattern_list R_BRACKET;
context         : macro_context? proced_context?;
macro_context   : 'MacroDefs' id;
proced_context  : 'Procedures' id;
pattern_list    : 'PatList' L_BRACKET (pattern_call)* R_BRACKET;
pattern_call    : id (L_BRACKET context R_BRACKET)?;

///////////////////////////////////////////////////////////////////////

pattern_exec_l      : pattern_exec+;
pattern_exec        : 'PatternExec' id? L_BRACKET pattern_burst_call* R_BRACKET;
pattern_burst_call  : 'PatternBurst' id;

///////////////////////////////////////////////////////////////////////

procedures_l    : procedures*;
procedures      : 'Procedures' id? L_BRACKET procedure* R_BRACKET;
procedure       : id L_BRACKET inst_list R_BRACKET;

///////////////////////////////////////////////////////////////////////

macros_l    : macros*;
macros      : 'MacroDefs' id? L_BRACKET macro* R_BRACKET;
macro       : id L_BRACKET inst_list R_BRACKET;

///////////////////////////////////////////////////////////////////////

pattern_l   : pattern*;
pattern     : 'Pattern' id L_BRACKET inst_list R_BRACKET;


///////////////////////////////////////////////////////////////////////

inst_list   : inst*;
inst        : label? (loop | shift | w_inst | c_inst | f_inst | v_inst | call_inst
            | goto_inst | stop_inst | scan_inst | 'IddqTestPoint');
label       : id ':';
loop        : 'Loop' INT L_BRACKET inst_list R_BRACKET;
shift       : 'Shift' L_BRACKET inst_list R_BRACKET;
w_inst      : 'W' id;
c_inst      : 'C' L_BRACKET assigs R_BRACKET;
f_inst      : 'F' L_BRACKET assigs R_BRACKET;
v_inst      : 'V' L_BRACKET assigs R_BRACKET;
call_inst   : ('Call' | 'Macro') id (L_BRACKET assigs R_BRACKET)?;
goto_inst   : 'GoTo' id;
stop_inst   : 'Stop';
scan_inst   : 'ScanChain' id;

assigs      : assig*;
assig       : id EQ assig_expr;
assig_expr  : JOIN? (repeat | wfc_extended)*;
repeat      : REPEAT INT wfc_extended;

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
wfc         : (CHARS | INT)+;
wfc_extended: (CHARS | INT | '#' | '%')+;
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
EXCLAMATION : '!';
QUOTE       : '\'';
JOIN        : '\\j';
REPEAT      : '\\r';

FLOAT   : INT'.'INT;
INT     : DIG+;
CHARS   : LETTER+;
STRING  : '"' ~('\r' | '\n' | '"')* '"';

fragment DIG    : [0-9];
fragment NUM    : INT | FLOAT;
fragment LETTER : [a-zA-Z];

// Ignored tokens (Order is important)
WHITE_SPACES    : [ \t\r\n;]+ -> skip;
COMMENT         : '//' ~('\r' | '\n')* -> skip;
ANNOTATION      : 'Ann ' L_BRACKET '*' ([ \p{S}\p{P}\p{M}\p{L}\p{N}])* '*' R_BRACKET -> skip;